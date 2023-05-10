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
norm_check_dir_path = "../../test/"

cmd = "touch " + out_filepath
run_cmd(cmd)

cmd = "norminette " + norm_check_dir_path +  " > " + out_filepath
run_cmd(cmd)

ignore1 = "OK"
ignore2 = "Error!"
ignore3 = "Missing or invalid 42 header"
with open(out_filepath) as f:
    for line in f:
        print(line)
        if ignore1 in line or ignore2 in line or ignore3 in line:
            continue
        print_color_str(RED, "[NG] ")
        exit(1)

print_color_str(GREEN, "[OK] ")
exit(0)