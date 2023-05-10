import subprocess

# ----------------------------------------------------------
# color
WHITE = "white"
RED = "red"
GREEN = "green"
color_dict = {"white" : "\033[37m",
              "red" : "\033[31m",
              "green" : "\033[32m",
              "end" : "\033[0m"}

def print_color_str(color=WHITE, text=""):
    print(color_dict[color] + text + color_dict["end"])

def print_color_str_no_lf(color=WHITE, text=""):
    print(color_dict[color] + text + color_dict["end"], end="")

# ----------------------------------------------------------
# run
def run_cmd(cmd):
    subprocess.run(cmd, shell=True)

# ----------------------------------------------------------
OUT_FILE = "norm_out.txt"
NORM_CHECK_PATH = "../../playground/"
# NORM_CHECK_PATH = "includes srcs"

cmd = "touch " + OUT_FILE
run_cmd(cmd)

cmd = "norminette " + NORM_CHECK_PATH +  " > " + OUT_FILE
run_cmd(cmd)

def put_lines(lines):
    for line in lines:
        print(line, end="")
    print("-----------------------")

LINE_OK = "OK"
LINE_ERR = "Error!"
LINE_HEADER = "INVALID_HEADER"
result = True
with open(OUT_FILE) as f:
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

if result:
    print_color_str(GREEN, "[OK] ")
    exit(0)
else:
    print_color_str(RED, "[NG] ")
    exit(1)
