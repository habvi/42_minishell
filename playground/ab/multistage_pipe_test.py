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
def run_cmd(cmd):
    return subprocess.run(cmd, capture_output=True, text=True, shell=True)

def run_minishell(cmd):
    res_minishell = run_cmd(cmd)
    print("=== minishell ===")
    print(cmd)
    print(f'[{res_minishell.stdout}]')
    # print(res_minishell.stderr)
    return res_minishell.stdout

def run_bash(cmd):
    res_bash = run_cmd(cmd)
    print("===== bash =====")
    print(cmd)
    print(f'[{res_bash.stdout}]')
    return res_bash.stdout

# ----------------------------------------------------------
# put
def put_result(result, ok, ko):
    if result:
        print_color_str(GREEN, "[OK]")
        ok += 1
    else:
        print_color_str(RED, "[KO]")
        ko += 1
    return ok, ko

def put_total_result(ok, ko):
    print()
    print(ok + ko, "test case / ", end="")
    print_color_str_no_lf(GREEN, "OK ")
    print(ok, ", ", end="")
    print_color_str_no_lf(RED, "KO ")
    print(ko)

# ----------------------------------------------------------
def main():
    cmd = "make multi"
    run_cmd(cmd)

    ok = 0
    ko = 0
    m_res = run_minishell(f'{PATH} "echo" "-e" "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" "|" "grep" "a" "|" "grep" "c"')
    b_res = run_bash('echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c')
    ok, ko = put_result(m_res == b_res, ok, ko)

    put_total_result(ok, ko)

if __name__ == '__main__':
    main()