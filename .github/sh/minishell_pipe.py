import subprocess
import shutil

# ----------------------------------------------------------
# OUT_FILE = "pipe_test_out.txt"
PATH = "./minishell"
PATH_BASH = "bash"

# ----------------------------------------------------------
# color
WHITE = "white"
RED = "red"
GREEN = "green"
YELLOW = "yellow"
COLOR_DICT = {"white" : "\033[37m",
              "red" : "\033[31m",
              "green" : "\033[32m",
              "yellow" : "\033[33m",
              "end" : "\033[0m"}

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
        if val_results[i] == "LEAK" and i <= val_res_len and val_results[i + 1] == "SUMMARY:":
            last_summary = sum_bytes
            sum_bytes = 0
            i += 2
            continue
        for lost in ("definitely", "indirectly", "possibly"):
            if val_results[i] == lost and i + 1 <= val_res_len and val_results[i + 2].isdigit():
                leak_bytes = int(val_results[i + 2])
                # print lost bytes
                # print(f'{lost}:{leak_bytes}')
                sum_bytes += leak_bytes

    # print valgrind result
    # print(f'\nvalgrind res:\n{stderr}')
    last_summary = sum_bytes
    if (last_summary > 0):
        is_leak_occurred = True
    return is_leak_occurred, last_summary

def run_cmd_with_valgrind(stdin=None, cmd=None):
    valgrind="valgrind "
    try:
        res = subprocess.run(valgrind + cmd, input=stdin, capture_output=True, text=True, shell=True, timeout=2)
        return res
    except subprocess.TimeoutExpired as e:
        print(e.cmd)

def run_minishell_with_valgrind(stdin, cmd):
    res_minishell = run_cmd_with_valgrind(stdin, cmd)
    print(f'cmd:{stdin}', end='\n')
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
    if shutil.which("valgrind") == None:
        # print("valgrind not found")
        return None, None

    leak_res_minishell = run_minishell_with_valgrind(stdin, PATH)
    leak_res_bash = run_bash_with_valgrind(stdin, PATH_BASH)
    return leak_res_minishell, leak_res_bash


# ----------------------------------------------------------
# run
def run_cmd(stdin=None, cmd=None):
    try:
        res = subprocess.run(cmd, input=stdin, capture_output=True, text=True, shell=True, timeout=2)
        return res
    except subprocess.TimeoutExpired as e:
        print(e.cmd)
        # print(e.returncode)
        # print(e.output)
        # print(e.stdout)
        # print(e.stderr)

def run_minishell(stdin, cmd):
    res_minishell = run_cmd(stdin, cmd)
    if res_minishell:
        print("=== minishell ===")
        print(cmd, len(res_minishell.stdout), "byte")
        print(f'[{res_minishell.stdout}]')
        # print(res_minishell.stderr)
        return res_minishell
    return None

def run_bash(stdin, cmd):
    res_bash = run_cmd(stdin, cmd)
    if res_bash:
        print("===== bash =====")
        print(cmd, len(res_bash.stdout), "byte")
        print(f'[{res_bash.stdout}]')
        # print(res_bash.stderr)
        return res_bash
    return None

def run_both(stdin):
    res_minishell = run_minishell(stdin, PATH)
    res_bash = run_bash(stdin, PATH_BASH)
    return res_minishell, res_bash

# ----------------------------------------------------------
# put
def put_result(val, m_res, b_res):
    test_num, _, _ = val
    if m_res is None or b_res is None:
        print_color_str(RED, f'[{test_num}. timeout]')
        # ko
        val[2] += 1
    elif (m_res.stdout == b_res.stdout) and (m_res.returncode == b_res.returncode):
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
        print_color_str(RED, f'[{test_num}. valgrind not found]')
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

def test(test_name, test_input_arr):
    test_res = 0
    print(f' ========================= {test_name} ========================= ')

    # output test
    test_num = 1
    ok = 0
    ko = 0
    val = [test_num, ok, ko]

    for stdin in test_input_arr:
        m_res, b_res = run_both(stdin)
        put_result(val, m_res, b_res)

    test_res |= put_total_result(val)

    # leak test
    leak_test_num = 1
    leak_ok = 0
    leak_ko = 0
    leak_skip = 0
    val_leak = [leak_test_num, leak_ok, leak_ko, leak_skip]

    for stdin in test_input_arr:
        m_res, b_res = run_both_with_valgrind(stdin)
        # print(f'm_res:{m_res}')
        put_leak_result(val_leak, m_res, b_res)

    test_res |= put_total_leak_result(val_leak)
    print()
    return test_res

# ----------------------------------------------------------
def main():
    test_res = 0

    pipe_test = ("/bin/ls -l",
             "/bin/echo abcde",
             "/bin/echo aaa bbb\n/bin/ls",
             "/bin/echo aa\n/bin/echo bb\n/bin/echo ccc",
             "/bin/echo aaa | /bin/grep a",
             "/bin/echo aaa | /bin/cat -e",
             "/bin/echo aaa | nothing",
             )
    test_res |= test("multi_pipe", pipe_test)


    # exit_status ...??
    echo_test = ("echo",
                 "echo a",
                 "echo a b c",
                 "echo a        b        c",
                 "echo a echo b echo c",
                 "echo aaaaaaaaaaaaaaaa bbbbbbbb  ccccccc echo   aa",
                 "echo /bin/echo a b c   d   e",
                 # "echo a \"\" b",
                 # "echo a \"\" \"\" \"\" b",
                 # "echo \"\"",
                 "echo -n hello",
                 "echo -n hello -n",
                 "echo -----n hello",
                 "echo -n -----n hello",
                 "echo -n -n -n -n -n  a  b  c",
                 "echo -n -n -n -n -n  a  b  c -n -n -n -m  d e f",
                 "echo -n -m hoge",
                 "echo - -n a b c",
                 "echo -n - -n a   b   c",
                 "echo -nnnnnnnnnnnnnnnnnnnnn a   b   c",
                 "echo -nnnnnnnnnmnnnnnnnnnnn a   b   c",
                 "echo -nnnnnn -n -n -n -nnnnnn a  -n -n -n   b",
                 "echo 123 456 -n  a b c  d",
                 "echo -N a b c",
                 "echo -n- a b c",
                 "echo n- a b c",
                 "echo -n-n a b c",
                 "echo nnnnnnn  -n a b c",
                 "echo nnnn- a b c",
                 )

    test_res |= test("ft_echo", echo_test)


    exit_test = ["exit",
                 "exit 0",
                 "exit 1",
                 "exit 42",
                 "exit -1",
                 "exit 2147483647",
                 "exit -2147483648",
                 "exit 9223372036854775807",
                 "exit -9223372036854775808",
                 "exit 0000000000000000000",
                 "exit 0000000000000000001",
                 # "exit \"  +42 \"",
                 "exit 1 1",
                 "exit -1 1",
                 "exit 1 1 1",
                 "exit 9223372036854775808",
                 "exit a",
                 "exit a b",
                 "exit a b c",
                 "exit a 1 b",
                 "exit a 1 1",
                 "exit a b 1",
                 "exit --1",
                 "exit -1+",
                 "exit -1+ a",
                 "exit -1+ 1",
                 "exit 9999999999999999999999999999999999999999999999999999999999999999",
                 "exit \t42",
                 "exit \n42",
                 "exit \v42",
                 "exit \f42",
                 "exit \r42",
                 ] # add more test after update tokenizer

    test_res |= test("ft_exit", exit_test)


    # stdin = "/bin/echo -e aaa\naacc\nbbb\nbbcc\nccc\naabb\nabc | /bin/grep a | /bin/grep c"
    # m_res, b_res = run_both(stdin)
    # put_result(val, m_res, b_res)

    # stdin = "/bin/cat | /bin/ls"
    # m_res, b_res = run_both(stdin)
    # put_result(val, m_res, b_res)

    # stdin = "abcde"
    # 'cat | echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c'

    # stdin = "aa\nbb\ncc\nbbaa\n"
    # "cat | cat | cat | grep b"

    exit(test_res)

if __name__ == '__main__':
    main()