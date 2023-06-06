import tempfile
import os
import subprocess
import shutil
from test_functions import test

# color
WHITE = "white"
RED = "red"
GREEN = "green"
YELLOW = "yellow"
MAGENTA = "magenta"
CYAN = "cyan"
COLOR_DICT = {"white": "\033[37m",
              "red": "\033[31m",
              "green": "\033[32m",
              "yellow": "\033[33m",
              "magenta": "\033[35m",
              "cyan": "\033[36m",
              "end": "\033[0m"}

BASH_PROMPT_PREFIX = "bash "
BASH_ERROR_PREFIX = "bash: line 1: "

BASH_INIT_FILE = 'bash_init_file'

STDOUT = 0
STDERR = 1
STATUS = 2
IS_EXITED = 3

def run_cmd(stdin=None, path=None):
    try:
        proc = subprocess.Popen(path,
                                stdin=subprocess.PIPE,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                text=True)

        stdout, stderr = proc.communicate(stdin, timeout=2)  # if sleep ...??
        if proc.poll() is None:
            is_exited = False
        else:
            is_exited = True
        res = [stdout, stderr, proc.returncode, is_exited]
        return res

    except subprocess.TimeoutExpired as e:
        print(e.cmd)
        # print(e.returncode)
        # print(e.output)
        # print(e.stdout)
        # print(e.stderr)
        return None

# rm prompt and error prefix
def get_eval_stderr(stderr, prompt_prefix, error_prefix):
    if stderr is None:
        return None

    errors = stderr.split('\n')
    print(f'errors:[{errors}]')
    if len(errors) > 0 and len(errors[-1]) == 0:
        del errors[-1]
    # if len(errors) > 0 and errors[-1] == "exit":  # for minishell
    #     del errors[-1]
    # print(f'errors:[{errors}]')
    err_list = [err for err in errors if not err.startswith(prompt_prefix)]
    # print(f'err_ls:[{err_list}]')
    for i in range(len(err_list)):
        # print(errors[i])
        if err_list[i].startswith(error_prefix):
            err_list[i] = err_list[i].removeprefix(error_prefix)
    # print(f'err_ls:[{err_list}]')

    return err_list

def run_shell(name, stdin, cmd, prompt_pfx, err_pfx):
    res = run_cmd(stdin, cmd)
    if res:
        print(f'=== {name} ===')
        print(cmd, len(res[STDOUT]), "byte")
        print(f' stdout:[{COLOR_DICT[CYAN] + res[STDOUT] + COLOR_DICT["end"]}]')
        errors = get_eval_stderr(res[STDERR], prompt_pfx, err_pfx)
        print(" stderr:[", end='')
        for i in range(len(errors)):
            print(COLOR_DICT[MAGENTA] + errors[i] + COLOR_DICT["end"], end='')
            if i + 1 < len(errors):
                print()
        print("]")
        print(f' status:{res[STATUS]}')
        print(f' exited:{res[IS_EXITED]}')
        res[STDERR] = errors
        return res
    return None

def main():
    PATH_BASH = ["bash", "--init-file", BASH_INIT_FILE, "-i"]
    inputs = ["tty", "exit", "exit 0"]

    try:
        with open(BASH_INIT_FILE, "w") as init_file:
            init_file.write(f'PS1="{BASH_PROMPT_PREFIX} "')

        for input in inputs:
            res_bash = run_shell("bash",
                                 input,
                                 PATH_BASH,
                                 BASH_PROMPT_PREFIX,
                                 BASH_ERROR_PREFIX)
    finally:
        if os.path.exists(BASH_INIT_FILE):
            os.remove(BASH_INIT_FILE)

if __name__ == '__main__':
    main()
