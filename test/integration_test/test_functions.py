import os
import shutil
import subprocess

# ----------------------------------------------------------
# OUT_FILE = "pipe_test_out.txt"
PATH_MINISHELL = ["./minishell", "-i"]
PATH_MINISHELL_LEAK = "./minishell"
BASH_INIT_FILE = 'bash_init_file'
PATH_BASH = ["/bin/bash", "--init-file", BASH_INIT_FILE, "-i"]
PATH_BASH_LEAK = "bash"

# ----------------------------------------------------------
MINISHELL_PROMPT_PREFIX = "minishell "
MINISHELL_ERROR_PREFIX = "minishell: "
BASH_PROMPT_PREFIX = "bash "
BASH_ERROR_PREFIX = "bash: "
GITHUB_ERROR_PREFIX = ["cannot set terminal", "no job"]
BASH_DROP_WORDS = ["usage:"]


VALGRIND = "valgrind"
VALGRIND_OP = " --track-fds=yes "

# ----------------------------------------------------------
STDOUT = 0
STDERR = 1
STATUS = 2
IS_EXITED = 3

# output test res
TEST_NO_IDX = 0
OK_IDX = 1
KO_IDX = 2
SKIP_IDX = 3

# valgrind test res
VAL_TEST_NO_IDX = 0
VAL_OK_IDX = 1
VAL_LEAK_NG_IDX = 2
VAL_FD_NG_IDX = 3
VAL_SKIP_IDX = 4

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

def get_leak_bytes(line):
    split = line.split()
    len_split = len(split)

    leak_bytes = 0
    for i in range(len_split):
        for lost in ("definitely", "indirectly", "possibly"):
            if split[i] == lost and i + 2 < len_split and split[i + 2].isdigit():
                leak_bytes = int(split[i + 2])
                # print(f'lost:{lost}, leak:[{split[i + 2]}]')
                break

    return leak_bytes


def get_valgrind_leak_summary(stderr):
    sum_bytes = 0
    val_results = stderr.split('\n')

    checked = [0, 0, 0]

    for line in reversed(val_results):
        # print(f'reversed_line:{line}')
        if "definitely" in line:
            sum_bytes += get_leak_bytes(line)
            checked[0] = 1
        if "indirectly" in line:
            sum_bytes += get_leak_bytes(line)
            checked[1] = 1
        if "possibly" in line:
            sum_bytes += get_leak_bytes(line)
            checked[2] = 1

        if sum(checked) == 3:
            break

    # print valgrind result
    # print(f'\nvalgrind res:\n{stderr}')
    return sum_bytes


def get_open_fd(line):
    split = line.split()
    len_split = len(split)

    # print(f'line:{line}, split:{split}')
    fd = 0
    for i in range(len_split):
        if split[i] == "DESCRIPTORS:" and split[i + 1].isdigit():
            fd = int(split[i + 1])
            # print(f'fd:{split[i + 1]}')
            break
    return fd


# FILE DESCRIPTORS: 3 open (3 std) at exit
def get_valgrind_fd_at_exit(stderr):

    val_results = stderr.split('\n')
    fd_at_exit = 0

    for line in reversed(val_results):
        if "FILE DESCRIPTORS:" in line:
            fd_at_exit = get_open_fd(line)
            break

    return fd_at_exit


def get_valgrind_res(stderr):
    leak_summary = get_valgrind_leak_summary(stderr)
    fd_at_exit = get_valgrind_fd_at_exit(stderr)
    return leak_summary, fd_at_exit


def run_cmd_with_valgrind(stdin=None, cmd=None):
    valgrind = VALGRIND + VALGRIND_OP
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
    if res_minishell is None or res_minishell.stderr is None:
        return None
    leak_bytes, fd_at_exit = get_valgrind_res(res_minishell.stderr)
    print(f' minishell leaks      : {leak_bytes} bytes')
    print(f'           fd at exit : {fd_at_exit} open (3 std)')
    return leak_bytes, fd_at_exit


def run_bash_with_valgrind(stdin, cmd):
    res_bash = run_cmd_with_valgrind(stdin, cmd)
    if res_bash is None or res_bash.stderr is None:
        return None
    leak_bytes, fd_at_exit = get_valgrind_res(res_bash.stderr)
    print(f' bash leaks           : {leak_bytes} bytes')
    return leak_bytes, fd_at_exit


def run_both_with_valgrind(stdin):
    print("===== leak and fd test =====")
    if shutil.which(VALGRIND) is None:
        return None, None

    leak_res_minishell = run_minishell_with_valgrind(stdin, PATH_MINISHELL_LEAK)
    # leak_res_bash = run_bash_with_valgrind(stdin, PATH_BASH_LEAK)
    # return leak_res_minishell, leak_res_bash
    return leak_res_minishell

# ----------------------------------------------------------
# remove prompt and error prefix

def remove_prompt_prefix(err_list, prompt_prefix):
    ret = []
    for err in err_list:
        if err.startswith(prompt_prefix):
            continue
        ret.append(err)
    return ret


def remove_error_prefix(err_list, error_prefix):
    ret = []
    for err in err_list:
        if err.startswith(error_prefix):
            err = err.removeprefix(error_prefix)
        ret.append(err)
    return ret


def remove_drop_words(err_list, drop_words):
    ret = []
    for err in err_list:
        drop = False
        for word in drop_words:
            if word in err:
                drop = True
        if not drop:
            ret.append(err)

    return ret


def remove_github_error(err_list, err_prefixes):
    ret = []
    for err in err_list:
        if any(err.startswith(prefix) for prefix in err_prefixes):
            continue
        ret.append(err)
    return ret


def get_eval_stderr(stderr, prompt_prefix, error_prefix):
    if stderr is None:
        return None

    errors = stderr.split('\n')
    # print(f'errors:[{errors}]')
    if len(errors) > 0 and len(errors[-1]) == 0:
        del errors[-1]

    err_list = remove_prompt_prefix(errors, prompt_prefix)
    err_list = remove_error_prefix(err_list, error_prefix)
    err_list = remove_drop_words(err_list, BASH_DROP_WORDS)
    err_list = remove_github_error(err_list, GITHUB_ERROR_PREFIX)

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
        print(f' stdin  : [{stdin}]')
        print(f' stdout : [{COLOR_DICT[CYAN] + res[STDOUT] + COLOR_DICT["end"]}]')
        errors = get_eval_stderr(res[STDERR], prompt_pfx, err_pfx)
        print(" stderr : [", end='')
        for i in range(len(errors)):
            print(COLOR_DICT[MAGENTA] + errors[i] + COLOR_DICT["end"], end='')
            if i + 1 < len(errors):
                print()
        print("]")
        print(f' status : {res[STATUS]}')
        print(f' exited : {res[IS_EXITED]}')
        print()
        res[STDERR] = errors
        return res
    return None


def run_both(test_no, stdin, status_only):
    print_cmd = get_cmd_string_for_output(stdin)
    print(f'{"-" * 50} TEST NO.{test_no} {"<STATUS ONLY>" if status_only else ""} {"-" * 50} ', end='\n')
    print(f' input cmd:[{print_cmd}]', end='\n')
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
def put_result(val, m_res, b_res, status_only):
    test_num, _, _ = val
    if m_res is None or b_res is None:
        print_color_str(RED, f'[{test_num}. timeout]')
        val[KO_IDX] += 1
    elif not status_only and m_res == b_res:
        print_color_str(GREEN, f'[{test_num}. OK]')
        val[OK_IDX] += 1
    elif status_only and m_res[STATUS] == b_res[STATUS]:
        print_color_str(GREEN, f'[{test_num}. OK]')
        val[OK_IDX] += 1
    else:
        print_color_str(RED, f'[{test_num}. KO]')
        val[KO_IDX] += 1

    val[TEST_NO_IDX] += 1
    print()


def put_valgrind_result(val_res, m_res):
    test_num, _, _, _, _= val_res
    if m_res is None:
        print_color_str(YELLOW, f'[{test_num}. valgrind not found]')
        val_res[VAL_SKIP_IDX] += 1

    is_leak, fd = m_res
    if not is_leak and fd == 3:
        print_color_str(GREEN, f'[{test_num}. OK]')
        val_res[VAL_OK_IDX] += 1
    if is_leak:
        print_color_str(RED, f'[{test_num}. LEAK KO]')
        val_res[VAL_LEAK_NG_IDX] += 1
    if fd != 3:
        print_color_str(RED, f'[{test_num}. FD KO]')
        val_res[VAL_FD_NG_IDX] += 1

    val_res[TEST_NO_IDX] += 1
    print()


# def add_val_to_leak(val, val_leak):
#     for i in range(len(val)):
#         val[i] += val_leak[i]

def put_total_valgrind_result(val_res):
    test_num, ok, leak_ng, fd_ng, skip = val_res
    print("#########################################")
    print(" LEAK TOTAL RESULT : ", end="")
    print_color_str_no_lf(GREEN, "OK ")
    print(f'{ok}, ', end="")
    print_color_str_no_lf(RED, "LEAK_NG ")
    print(f'{leak_ng}, ', end="")
    print_color_str_no_lf(RED, "FD_NG ")
    print(f'{fd_ng}, ', end="")
    print_color_str_no_lf(YELLOW, "SKIP ")
    print(skip, end="")
    print(f' (test case: {test_num - 1})')
    print("#########################################\n")
    if ok == test_num - 1:
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

def output_test(test_input_list, status_only):
    test_num = 1
    ok = 0
    ko = 0
    val = [test_num, ok, ko]
    ko_case = []
    prev_ko = 0
    test_no = 1

    for stdin in test_input_list:
        m_res, b_res = run_both(test_no, stdin, status_only)
        put_result(val, m_res, b_res, status_only)
        test_no += 1
        if prev_ko != val[2]:
            ko_case.append(stdin)
        prev_ko = val[2]

    return put_total_result(val), ko_case


def valgrind_test(test_input_list):
    test_num = 1
    ok = 0
    leak_ng = 0
    fd_ng = 0
    skip = 0
    val_result = [test_num, ok, leak_ng, fd_ng, skip]

    ko_case = []
    prev_ok = 0

    for stdin in test_input_list:
        m_res = run_both_with_valgrind(stdin)
        put_valgrind_result(val_result, m_res)
        if prev_ok == val_result[VAL_OK_IDX]:
            ko_case.append(stdin)
        prev_ok = val_result[VAL_OK_IDX]

    # print(f'val ko:{ko_case}')
    # print(f'val result:{val_result}')
    return put_total_valgrind_result(val_result), ko_case


# ----------------------------------------------------------

def print_ko_case(test_name, test_res, out_ko_case, val_ko_case):
    if test_res:
        print(f"{COLOR_DICT[RED]}"
              "#########################################")
        print("#####            KO CASE            #####")
        print("#########################################"
              f"{COLOR_DICT['end']}")

        with open(f'ko_case_{test_name}.txt', 'w') as f:
            if len(out_ko_case):
                print(f'[OUTPUT KO CASE OF : {test_name}]')
                f.write(f'[OUTPUT KO CASE OF : {test_name}]\n')
                for ko in out_ko_case:
                    print(ko)
                    f.write(f'{ko}\n')

            if len(val_ko_case):
                print(f'[LEAK or FD KO CASE OF : {test_name}]')
                f.write(f'[LEAK or FD KO CASE OF : {test_name}]\n')
                for ko in val_ko_case:
                    print(ko)
                    f.write(f'{ko}\n')


def test(test_name, test_input_list, status_only):
    try:
        with open(BASH_INIT_FILE, "w") as init_file:
            init_file.write(f'PS1="{BASH_PROMPT_PREFIX} "')

        test_res = 0
        print(f' ========================= TEST : [{test_name} {" STATUS ONLY" if status_only else ""}] ========================= ')

        output_res, out_ko_case = output_test(test_input_list, status_only)
        test_res |= output_res

        val_res, val_ko_case = valgrind_test(test_input_list)
        test_res |= val_res
        print()

        if os.path.isfile(f'ko_case_{test_name}.txt'):
            os.remove(f'ko_case_{test_name}.txt')
        print_ko_case(test_name, test_res, out_ko_case, val_ko_case)
        print()

    finally:
        if os.path.exists(BASH_INIT_FILE):
            os.remove(BASH_INIT_FILE)

    return test_res

# ----------------------------------------------------------
