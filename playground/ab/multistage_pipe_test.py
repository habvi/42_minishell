import subprocess

# ----------------------------------------------------------
# python3 multistage_pipe_test.py
PATH = "./a.out"

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

def run_cmd_shell_false(stdin=None, cmd=None):
    try:
        res = subprocess.run(cmd, input=stdin, capture_output=True, text=True, shell=False, timeout=2)
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
        print(cmd)
        print(f'[{res_minishell.stdout}]')
        # print(res_minishell.stderr)
        return res_minishell
    return None

def run_bash(stdin, cmd):
    res_bash = run_cmd(stdin, cmd)
    if res_bash:
        print("===== bash =====")
        print(cmd)
        print(f'[{res_bash.stdout}]')
        return res_bash
    return None

# def run_both(stdin, cmd):
#     m_cmd = [PATH] + cmd.split()
#     res_minishell = run_cmd_shell_false(stdin, m_cmd)
#     print("=== minishell ===")
#     print(m_cmd, len(res_minishell.stdout))
#     print(f'[{res_minishell.stdout}]')

#     b_cmd = cmd
#     res_bash = run_cmd(stdin, b_cmd)
#     print("===== bash =====")
#     print(b_cmd, len(res_bash.stdout))
#     print(f'[{res_bash.stdout}]')
#     print(res_minishell == res_bash)
#     return res_minishell, res_bash

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

def put_total_result(val):
    test_num, ok, ko = val
    print()
    print_color_str_no_lf(GREEN, "OK ")
    print(f'{ok}, ', end="")
    print_color_str_no_lf(RED, "KO ")
    print(ko, end="")
    print(f' (test case: {test_num - 1})')

# ----------------------------------------------------------
def main():
    test_num = 1
    ok = 0
    ko = 0
    val = [test_num, ok, ko]

    cmd = "make multi"
    run_cmd(None, cmd)

    # m_res, b_res = run_both(None, "echo a")
    # ok, ko = put_result(m_res, b_res, ok, ko)

    stdin = None
    m_res = run_minishell(stdin, f'{PATH} "echo" "-e" "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" "|" "grep" "a" "|" "grep" "c"')
    b_res = run_bash(stdin, 'echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c')
    put_result(val, m_res, b_res)

    stdin = None
    m_res = run_minishell(stdin, f'{PATH} "echo" "a"')
    b_res = run_bash(stdin, "echo a")
    put_result(val, m_res, b_res)

    stdin = "abcde"
    m_res = run_minishell(stdin, f'{PATH} "cat" "|" "echo" "-e" "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" "|" "grep" "a" "|" "grep" "c"')
    b_res = run_bash(stdin, 'cat | echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c')
    put_result(val, m_res, b_res)

    stdin = None
    m_res = run_minishell(stdin, f'{PATH} "echo" "a" "|" "echo" "bb" "|" "echo" "ccc"')
    b_res = run_bash(stdin, "echo a | echo bb | echo ccc")
    put_result(val, m_res, b_res)

    stdin = "aaa"
    m_res = run_minishell(stdin, f'{PATH} "cat" "|" "ls"')
    b_res = run_bash(stdin, "cat | ls")
    put_result(val, m_res, b_res)

    stdin = "aa\nbb\ncc\nbbaa\n"
    m_res = run_minishell(stdin, f'{PATH} "cat" "|" "cat" "|" "cat" "|" "grep" "b"')
    b_res = run_bash(stdin, "cat | cat | cat | grep b")
    put_result(val, m_res, b_res)

    put_total_result(val)

if __name__ == '__main__':
    main()