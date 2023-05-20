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
    return subprocess.run(cmd, input=stdin, capture_output=True, text=True, shell=True)

def run_cmd_shell_false(stdin=None, cmd=None):
    return subprocess.run(cmd, input=stdin, capture_output=True, text=True, shell=False)

def run_minishell(stdin, cmd):
    res_minishell = run_cmd(stdin, cmd)
    print("=== minishell ===")
    print(cmd)
    print(f'[{res_minishell.stdout}]')
    # print(res_minishell.stderr)
    return res_minishell.stdout

def run_bash(stdin, cmd):
    res_bash = run_cmd(stdin, cmd)
    print("===== bash =====")
    print(cmd)
    print(f'[{res_bash.stdout}]')
    return res_bash.stdout

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
def put_result(m_res, b_res, ok, ko):
    if m_res == b_res:
        print_color_str(GREEN, "[OK]")
        ok += 1
    else:
        print_color_str(RED, "[KO]")
        ko += 1
    return ok, ko

def put_total_result(ok, ko):
    print()
    print_color_str_no_lf(GREEN, "OK ")
    print(f'{ok}, ', end="")
    print_color_str_no_lf(RED, "KO ")
    print(ko, end="")
    print(f' (test case: {ok + ko})')

# ----------------------------------------------------------
def main():
    cmd = "make multi"
    run_cmd(None, cmd)

    ok = 0
    ko = 0

    # m_res, b_res = run_both(None, "echo a")
    # ok, ko = put_result(m_res, b_res, ok, ko)

    m_res = run_minishell(None, f'{PATH} "echo" "-e" "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" "|" "grep" "a" "|" "grep" "c"')
    b_res = run_bash(None, 'echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c')
    ok, ko = put_result(m_res, b_res, ok, ko)

    m_res = run_minishell(None, f'{PATH} "echo" "a"')
    b_res = run_bash(None, "echo a")
    ok, ko = put_result(m_res, b_res, ok, ko)

    stdin = "abcde"
    m_res = run_minishell(stdin, f'{PATH} "cat" "|" "echo" "-e" "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" "|" "grep" "a" "|" "grep" "c"')
    b_res = run_bash(stdin, 'cat | echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c')
    ok, ko = put_result(m_res, b_res, ok, ko)

    m_res = run_minishell(None, f'{PATH} "echo" "a" "|" "echo" "bb" "|" "echo" "ccc"')
    b_res = run_bash(None, "echo a | echo bb | echo ccc")
    ok, ko = put_result(m_res, b_res, ok, ko)

    put_total_result(ok, ko)

if __name__ == '__main__':
    main()