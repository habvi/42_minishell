import subprocess
import sys

# ----------------------------------------------------------
OUT_FILE = "norm_out.txt"
NORM_CHECK_PATH_ACTIONS = "includes srcs libft"
NORM_CHECK_PATH_LOCAL = "playground"

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
    subprocess.run(cmd, shell=True)

# ----------------------------------------------------------
# put
def debug_lines(lines):
    for line in lines:
        print(line, end="")
    print("-----------------------")

def put_result(passed):
    if passed:
        print_color_str(GREEN, "[OK]")
        exit(0)
    else:
        print_color_str(RED, "[NG]")
        exit(1)

# ----------------------------------------------------------
def check_each_file(lines):
    if len(lines) >= 2:
        debug_lines(lines)
        return False
    return True

def norm_check_exclude_header():
    LINE_OK = "OK!"
    LINE_ERR = "Error!"
    LINE_HEADER = "INVALID_HEADER"
    LINE_COMMENT = "WRONG_SCOPE_COMMENT"
    LINE_EMPTY = "EMPTY_LINE_FUNCTION"
    LINE_GLOBAL = "GLOBAL_VAR_DETECTED"
    passed = True
    with open(OUT_FILE) as f:
        try:
            lines = []
            for line in f:
                if LINE_ERR in line:
                    passed &= check_each_file(lines)
                    lines = [line]
                else:
                    if LINE_HEADER in line or LINE_OK in line:
                        continue
                    if LINE_COMMENT in line or LINE_EMPTY in line:
                        continue
                    if LINE_GLOBAL in line or LINE_EMPTY in line:
                        continue
                    lines.append(line)
            passed &= check_each_file(lines)
            return passed
        except FileNotFoundError as err:
            print(err)
            exit(1)

def run_norm(check_path):
    cmd = "python3 -m norminette " + check_path +  " > " + OUT_FILE
    print(cmd)
    run_cmd(cmd)

    passed = norm_check_exclude_header()
    return passed

def main():
    argc = len(sys.argv)
    if argc == 1:
        path = NORM_CHECK_PATH_ACTIONS
    elif argc == 2 and sys.argv[1] == "local":
        path = NORM_CHECK_PATH_LOCAL
    else:
        print("<python3 norm.py> or <python3 norm.py local>")
        exit(1)
    passed = run_norm(path)
    put_result(passed)

if __name__ == '__main__':
    main()