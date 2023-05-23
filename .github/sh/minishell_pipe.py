import subprocess

# ----------------------------------------------------------
# OUT_FILE = "pipe_test_out.txt"
PATH = "./minishell"

# ----------------------------------------------------------
# color
WHITE = "white"
RED = "red"
GREEN = "green"
COLOR_DICT = {"white" : "\033[37m",
              "red" : "\033[31m",
              "green" : "\033[32m",
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
    summary_no = 0
    last_summary = 0

    # print(stderr)
    results = stderr.split()
    for i in range(len(results)):
        if (results[i] == "LEAK" and results[i + 1] == "SUMMARY:"):
            last_summary = sum_bytes
            sum_bytes = 0
            summary_no += 1
        for lost in ["definitely", "indirectly", "possibly"]:
            if (results[i] == lost and results[i + 2].isdigit()):
                leak_bytes = int(results[i + 2])
                # print lost bytes
                # print(f'{lost}:{leak_bytes}')
                is_leak_occurred = True
                sum_bytes += leak_bytes

    # print valgrind result
    # print(f'\nvalgrind res:\n{stderr}')
    last_summary = sum_bytes
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
        print("=== minishell(leaks) ===")
        is_leak, leak_bytes = get_leak_res(res_minishell.stderr)
        print(f'lesk : {leak_bytes} bytes')
        return is_leak
    return None

def run_bash_with_valgrind(stdin, cmd):
    res_bash = run_cmd_with_valgrind(stdin, cmd)
    if res_bash.stderr:
        print("===== bash(leaks) =====")
        is_leak, leak_bytes = get_leak_res(res_bash.stderr)
        print(f'lesk : {leak_bytes} bytes')
        return is_leak
    return None

def run_both_with_valgrind(stdin):
    leak_res_minishell = run_minishell_with_valgrind(stdin, PATH)
    leak_res_bash = run_bash_with_valgrind(None, stdin)
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
    res_bash = run_bash(None, stdin)
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


def put_leak_result(val_leak, m_res, b_res):
    test_num, _, _ = val_leak
    if m_res is None or b_res is None:
        print_color_str(RED, f'[{test_num}. timeout]')
        # ko
        val_leak[2] += 1
    elif (m_res == False):
        print_color_str(GREEN, f'[{test_num}. OK]')
        # ok
        val_leak[1] += 1
    else:
        print_color_str(RED, f'[{test_num}. KO]')
        # ko
        val_leak[2] += 1
    # test_num
    val_leak[0] += 1
    print()

def add_val_to_leak(val, val_leak):
    for i in range(len(val)):
        val[i] += val_leak[i]

def put_total_result(val):
    test_num, ok, ko = val
    print()
    print_color_str_no_lf(GREEN, "OK ")
    print(f'{ok}, ', end="")
    print_color_str_no_lf(RED, "KO ")
    print(ko, end="")
    print(f' (test case: {test_num - 1})')
    if ok == test_num - 1:
        exit(0)
    else:
        exit(1)

# ----------------------------------------------------------
def main():
    test_num = 1
    ok = 0
    ko = 0
    val = [test_num, ok, ko]
    val_leak = [test_num, ok, ko]

    stdin = "/bin/ls -l"
    m_res, b_res = run_both(stdin)
    put_result(val, m_res, b_res)

    stdin = "/bin/echo abcde"
    m_res, b_res = run_both(stdin)
    put_result(val, m_res, b_res)

    stdin = "/bin/echo aaa bbb\n/bin/ls"
    m_res, b_res = run_both(stdin)
    put_result(val, m_res, b_res)

    stdin = "/bin/echo aa\n/bin/echo bb\n/bin/echo ccc"
    m_res, b_res = run_both(stdin)
    put_result(val, m_res, b_res)

    stdin = "/bin/echo aaa | /bin/grep a"
    m_res, b_res = run_both(stdin)
    put_result(val, m_res, b_res)


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


    print("----- valgdind -----\n")

    # why leak ??
    stdin = "/bin/echo aaa | /bin/cat -e"
    m_res, b_res = run_both_with_valgrind(stdin)
    put_leak_result(val, m_res, b_res)

    # leak
    stdin = "/bin/echo aaa | nothing"
    m_res, b_res = run_both_with_valgrind(stdin)
    put_leak_result(val, m_res, b_res)

    put_total_result(val)

if __name__ == '__main__':
    main()