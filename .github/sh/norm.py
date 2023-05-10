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
out_filepath = "norm_out.txt"
# norm_check_dir_path = "../../test/"
norm_check_dir_path = "test"

cmd = "touch " + out_filepath
run_cmd(cmd)

cmd = "norminette " + norm_check_dir_path +  " > " + out_filepath
run_cmd(cmd)

def put_lines(lines):
    for line in lines:
        print(line, end="")
    print("-----------------------")

line_ok = "OK"
line_err = "Error!"
line_header = "Missing or invalid 42 header"
result = True
with open(out_filepath) as f:
    lines = []
    for line in f:
        if line_err in line:
            if len(lines) >= 2:
                put_lines(lines)
                result = False
            lines = [line]
        else:
            if line_header in line:
                continue
            lines.append(line)

if result:
    print_color_str(GREEN, "[OK] ")
    exit(0)
else:
    print_color_str(RED, "[NG] ")
    exit(1)
