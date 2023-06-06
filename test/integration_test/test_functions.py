import os
import shutil
import subprocess

# ----------------------------------------------------------
# OUT_FILE = "pipe_test_out.txt"
PATH_MINISHELL = "./minishell"
BASH_INIT_FILE = 'bash_init_file'
PATH_BASH = ["bash", "--init-file", BASH_INIT_FILE, "-i"]
PATH_BASH_LEAK = "bash"

# ----------------------------------------------------------
MINISHELL_PROMPT_PREFIX = "minishell "
MINISHELL_ERROR_PREFIX = "minishell: "
BASH_PROMPT_PREFIX = "bash "
BASH_ERROR_PREFIX = "bash: "

# ----------------------------------------------------------
STDOUT = 0
STDERR = 1
STATUS = 2
IS_EXITED = 3

# ----------------------------------------------------------
# color
WHITE = "white"
RED = "red"
GREEN = "green"
YELLOW = "yellow"
MAGENTA = "magenta"
CYAN = "cyan"
COLOR_DICT = {"white": "\033[37m",
              "red": "\033[31m",
              "green": "\033[32m",
              "yellow": "\033[33m",
              "magenta": "\033[35m",
              "cyan": "\033[36m",
              "end": "\033[0m"}

# ----------------------------------------------------------

def print_color_str(color=WHITE, text=""):
    print(COLOR_DICT[color] + text + COLOR_DICT["end"])


def print_color_str_no_lf(color=WHITE, text=""):
    print(COLOR_DICT[color] + text + COLOR_DICT["end"], end="")


# ----------------------------------------------------------
# res_valgrind

def get_leak_res(stderr):
    is_leak_occurred = False
    sum_bytes = 0
    last_summary = 0
    val_results = stderr.split()
    val_res_len = len(val_results)

    for i in range(val_res_len):
        if val_results[i] == "LEAK" \
                and i <= val_res_len \
                and val_results[i + 1] == "SUMMARY:":
            last_summary = sum_bytes
            sum_bytes = 0
            i += 2
            continue
        for lost in ("definitely", "indirectly", "possibly"):
            if val_results[i] == lost \
                    and i + 1 <= val_res_len \
                    and val_results[i + 2].isdigit():
                leak_bytes = int(val_results[i + 2])
                # print lost bytes
                # print(f'{lost}:{leak_bytes}')
                sum_bytes += leak_bytes

    # print valgrind result
    # print(f'\nvalgrind res:\n{stderr}')
    last_summary = sum_bytes
    if last_summary > 0:
        is_leak_occurred = True
    return is_leak_occurred, last_summary


def run_cmd_with_valgrind(stdin=None, cmd=None):
    valgrind = "valgrind "
    try:
        res = subprocess.run(valgrind + cmd,
                             input=stdin,
                             capture_output=True,
                             text=True,
                             shell=True,
                             timeout=2)
        return res
    except subprocess.TimeoutExpired as e:
        print(e.cmd)


def run_minishell_with_valgrind(stdin, cmd):
    res_minishell = run_cmd_with_valgrind(stdin, cmd)
    print(f'cmd:[{stdin}]', end='\n')
    if res_minishell.stderr:
        is_leak, leak_bytes = get_leak_res(res_minishell.stderr)
        print(f' minishell leaks : {leak_bytes} bytes')
        return is_leak
    return None


def run_bash_with_valgrind(stdin, cmd):
    res_bash = run_cmd_with_valgrind(stdin, cmd)
    if res_bash.stderr:
        is_leak, leak_bytes = get_leak_res(res_bash.stderr)
        print(f' bash leaks      : {leak_bytes} bytes')
        return is_leak
    return None


def run_both_with_valgrind(stdin):
    print("===== leak test =====")
    if shutil.which("valgrind") is None:
        # print("valgrind not found")
        return None, None

    leak_res_minishell = run_minishell_with_valgrind(stdin, PATH_MINISHELL)
    leak_res_bash = run_bash_with_valgrind(stdin, PATH_BASH_LEAK)
    return leak_res_minishell, leak_res_bash


# ----------------------------------------------------------

# rm prompt and error prefix
def get_eval_stderr(stderr, prompt_prefix, error_prefix):
    if stderr is None:
        return None

    errors = stderr.split('\n')
    print(f'errors:[{errors}]')
    if len(errors) > 0 and len(errors[-1]) == 0:
        del errors[-1]
    # print(f'errors:[{errors}]')
    err_list = [err for err in errors if not err.startswith(prompt_prefix)]
    # print(f'err_ls:[{err_list}]')
    for i in range(len(err_list)):
        # print(errors[i])
        if err_list[i].startswith(error_prefix):
            err_list[i] = err_list[i].removeprefix(error_prefix)
    # print(f'err_ls:[{err_list}]')

    return err_list

# ----------------------------------------------------------
# run

def run_cmd(stdin=None, path=None):
    try:
        proc = subprocess.Popen(path,
                                stdin=subprocess.PIPE,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                text=True)

        stdout, stderr = proc.communicate(stdin, timeout=2)
        if proc.poll() is None:
            is_exited = False
        else:
            is_exited = True
        res = [stdout, stderr, proc.returncode, is_exited]
        return res

    except subprocess.TimeoutExpired as e:
        print(e.cmd)
        # print(e.returncode)
        # print(e.output)
        # print(e.stdout)
        # print(e.stderr)
        return None


def get_cmd_string_for_output(stdin):
    print_cmd = stdin \
        .replace("\t", "\\t") \
        .replace("\n", "\\n") \
        .replace("\v", "\\v") \
        .replace("\f", "\\f") \
        .replace("\r", "\\r")
    return print_cmd


def run_shell(name, stdin, cmd, prompt_pfx, err_pfx):
    res = run_cmd(stdin, cmd)
    if res:
        print(f'=== {name} ===')
        print(cmd, len(res[STDOUT]), "byte")
        print(f' stdout:[{COLOR_DICT[CYAN] + res[STDOUT] + COLOR_DICT["end"]}]')
        errors = get_eval_stderr(res[STDERR], prompt_pfx, err_pfx)
        print(" stderr:[", end='')
        for i in range(len(errors)):
            print(COLOR_DICT[MAGENTA] + errors[i] + COLOR_DICT["end"], end='')
            if i + 1 < len(errors):
                print()
        print("]")
        print(f' status:{res[STATUS]}')
        print(f' exited:{res[IS_EXITED]}')
        res[STDERR] = errors
        return res
    return None


def run_both(stdin):
    print_cmd = get_cmd_string_for_output(stdin)
    print(f'input cmd:[{print_cmd}]', end='\n')
    res_minishell = run_shell("minishell",
                              stdin,
                              PATH_MINISHELL,
                              MINISHELL_PROMPT_PREFIX,
                              MINISHELL_ERROR_PREFIX)
    res_bash = run_shell("bash",
                         stdin,
                         PATH_BASH,
                         BASH_PROMPT_PREFIX,
                         BASH_ERROR_PREFIX)

    return res_minishell, res_bash


# ----------------------------------------------------------
# put
def put_result(val, m_res, b_res):
    test_num, _, _ = val
    if m_res is None or b_res is None:
        print_color_str(RED, f'[{test_num}. timeout]')
        # ko
        val[2] += 1
    elif m_res == b_res:
        print_color_str(GREEN, f'[{test_num}. OK]')
        # ok
        val[1] += 1
    else:
        print_color_str(RED, f'[{test_num}. KO]')
        # ko
        val[2] += 1
    # test_num
    val[0] += 1
    print()


LEAK_OK = 1
LEAK_KO = 2
LEAK_SKIP = 3


def put_leak_result(val_leak, m_res, b_res):
    test_num, _, _, _ = val_leak
    if m_res is None or b_res is None:
        print_color_str(YELLOW, f'[{test_num}. valgrind not found]')
        # skip
        val_leak[LEAK_SKIP] += 1
    elif (m_res == False):
        print_color_str(GREEN, f'[{test_num}. OK]')
        # ok
        val_leak[LEAK_OK] += 1
    else:
        print_color_str(RED, f'[{test_num}. KO]')
        # ko
        val_leak[LEAK_KO] += 1
    # test_num
    val_leak[0] += 1
    print()


# def add_val_to_leak(val, val_leak):
#     for i in range(len(val)):
#         val[i] += val_leak[i]

def put_total_leak_result(val_leak):
    test_num, ok, ko, skip = val_leak
    print("#########################################")
    print(" LEAK TOTAL RESULT : ", end="")
    print_color_str_no_lf(GREEN, "OK ")
    print(f'{ok}, ', end="")
    print_color_str_no_lf(RED, "KO ")
    print(f'{ko}, ', end="")
    print_color_str_no_lf(YELLOW, "SKIP ")
    print(skip, end="")
    print(f' (test case: {test_num - 1})')
    print("#########################################\n")
    if ko == 0:
        return 0
    else:
        return 1


def put_total_result(val):
    test_num, ok, ko = val
    print("#########################################")
    print(" TOTAL RESULT : ", end="")
    print_color_str_no_lf(GREEN, "OK ")
    print(f'{ok}, ', end="")
    print_color_str_no_lf(RED, "KO ")
    print(ko, end="")
    print(f' (test case: {test_num - 1})')
    print("#########################################\n")
    if ok == test_num - 1:
        return 0
    else:
        return 1


# ----------------------------------------------------------

def test(test_name, test_input_list):
    try:
        with open(BASH_INIT_FILE, "w") as init_file:
            init_file.write(f'PS1="{BASH_PROMPT_PREFIX} "')

        test_res = 0
        print(f' ========================= {test_name} ========================= ')

        # output test
        test_num = 1
        ok = 0
        ko = 0
        val = [test_num, ok, ko]

        for stdin in test_input_list:
            m_res, b_res = run_both(stdin)
            put_result(val, m_res, b_res)

        test_res |= put_total_result(val)

        # leak test
        leak_test_num = 1
        leak_ok = 0
        leak_ko = 0
        leak_skip = 0
        val_leak = [leak_test_num, leak_ok, leak_ko, leak_skip]

        for stdin in test_input_list:
            m_res, b_res = run_both_with_valgrind(stdin)
            print(f'm_res:{m_res}')
            put_leak_result(val_leak, m_res, b_res)

        test_res |= put_total_leak_result(val_leak)
        print()

    finally:
        if os.path.exists(BASH_INIT_FILE):
            os.remove(BASH_INIT_FILE)

    return test_res

# ----------------------------------------------------------
