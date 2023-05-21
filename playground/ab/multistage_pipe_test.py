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
        res = subprocess.run(cmd, input=stdin, capture_output=True, text=True, shell=True, timeout=1)
        return res
    except subprocess.TimeoutExpired as e:
        print(e.cmd)
        # print(e.returncode)
        # print(e.output)
        # print(e.stdout)
        # print(e.stderr)

def run_cmd_shell_false(stdin=None, cmd=None):
    try:
        res = subprocess.run(cmd, input=stdin, capture_output=True, text=True, shell=False, timeout=1)
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
def put_result(test_num, m_res, b_res, ok, ko):
    if m_res is None or b_res is None:
        print_color_str(RED, f'[{test_num}. timeout]')
        ko += 1
    elif (m_res.stdout == b_res.stdout) and (m_res.returncode == b_res.returncode):
        print_color_str(GREEN, f'[{test_num}. OK]')
        ok += 1
    else:
        print_color_str(RED, f'[{test_num}. KO]')
        ko += 1
    return test_num + 1, ok, ko

def put_total_result(ok, ko):
    print()
    print_color_str_no_lf(GREEN, "OK ")
    print(f'{ok}, ', end="")
    print_color_str_no_lf(RED, "KO ")
    print(ko, end="")
    print(f' (test case: {ok + ko})')

# ----------------------------------------------------------
def main():
    test_num = 1

    cmd = "make multi"
    run_cmd(None, cmd)

    ok = 0
    ko = 0

    # m_res, b_res = run_both(None, "echo a")
    # ok, ko = put_result(m_res, b_res, ok, ko)

    m_res = run_minishell(None, f'{PATH} "echo" "-e" "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" "|" "grep" "a" "|" "grep" "c"')
    b_res = run_bash(None, 'echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c')
    test_num, ok, ko = put_result(test_num, m_res, b_res, ok, ko)

    m_res = run_minishell(None, f'{PATH} "echo" "a"')
    b_res = run_bash(None, "echo a")
    test_num, ok, ko = put_result(test_num, m_res, b_res, ok, ko)

    stdin = "abcde"
    m_res = run_minishell(stdin, f'{PATH} "cat" "|" "echo" "-e" "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" "|" "grep" "a" "|" "grep" "c"')
    b_res = run_bash(stdin, 'cat | echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c')
    test_num, ok, ko = put_result(test_num, m_res, b_res, ok, ko)

    m_res = run_minishell(None, f'{PATH} "echo" "a" "|" "echo" "bb" "|" "echo" "ccc"')
    b_res = run_bash(None, "echo a | echo bb | echo ccc")
    test_num, ok, ko = put_result(test_num, m_res, b_res, ok, ko)

    stdin = "abcde"
    m_res = run_minishell(None, f'{PATH} "cat" "|" "cat" "|" "cat" "|" "ls"')
    b_res = run_bash(None, "cat | cat | cat | ls")
    test_num, ok, ko = put_result(test_num, m_res, b_res, ok, ko)

    put_total_result(ok, ko)

if __name__ == '__main__':
    main()