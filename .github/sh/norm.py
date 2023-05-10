import subprocess
import sys

# ----------------------------------------------------------
# actions
# python3 norm.py

# local
# python3 norm.py local

# ----------------------------------------------------------
OUT_FILE = "norm_out.txt"
NORM_CHECK_PATH_ACTIONS = "includes srcs"
NORM_CHECK_PATH_LOCAL = "../../playground/"

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
def put_lines(lines):
    for line in lines:
        print(line, end="")
    print("-----------------------")

def put_result(result):
    if result:
        print_color_str(GREEN, "[OK]")
        exit(0)
    else:
        print_color_str(RED, "[NG]")
        exit(1)

# ----------------------------------------------------------
def norm_check_exclude_header():
    LINE_OK = "OK"
    LINE_ERR = "Error!"
    LINE_HEADER = "INVALID_HEADER"
    result = True
    with open(OUT_FILE) as f:
        try:
            lines = []
            for line in f:
                if LINE_ERR in line:
                    if len(lines) >= 2:
                        put_lines(lines)
                        result = False
                    lines = [line]
                else:
                    if LINE_HEADER in line:
                        continue
                    lines.append(line)
            return result
        except FileNotFoundError as err:
            print(err)
            exit(1)

def run_norm(check_path):
    cmd = "touch " + OUT_FILE
    run_cmd(cmd)

    cmd = "norminette " + check_path +  " > " + OUT_FILE
    run_cmd(cmd)

    result = norm_check_exclude_header()
    return result

def main():
    argc = len(sys.argv)
    if argc == 1:
        path = NORM_CHECK_PATH_ACTIONS
    elif argc == 2 and sys.argv[1] == "local":
        path = NORM_CHECK_PATH_LOCAL
    else:
        print("<python3 norm.py> or <python3 norm.py local>")
        exit(1)
    result = run_norm(path)
    put_result(result)

if __name__ == '__main__':
    main()