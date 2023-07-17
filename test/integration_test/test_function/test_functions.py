import os
import sys
sys.path.append(os.path.join(os.path.dirname(__file__), '.'))

from test_output import output_test
from test_valgrind import valgrind_test
from color import RED, COLOR_DICT

# ----------------------------------------------------------
# OUT_FILE = "pipe_test_out.txt"
PATH_MINISHELL = ["./minishell", "-i"]
PATH_MINISHELL_LEAK = "./minishell"
BASH_INIT_FILE = 'bash_init_file'
PATH_BASH = ["/bin/bash", "--init-file", BASH_INIT_FILE, "-i"]
PATH_BASH_LEAK = "bash"

# ----------------------------------------------------------
MINISHELL_PROMPT_PREFIX = "minishell "
MINISHELL_ERROR_PREFIX = "minishell: "
BASH_PROMPT_PREFIX = "bash "
BASH_ERROR_PREFIX = "bash: "
GITHUB_ERROR_PREFIX = ["cannot set terminal", "no job"]
BASH_DROP_WORDS = ["usage:"]

VALGRIND = "valgrind"
VALGRIND_OP = " --track-fds=yes "

# valgrind str
DEFINITELY = "definitely"
INDIRECTLY = "indirectly"
POSSIBLY = "possibly"
FD_FLAG = "DESCRIPTORS:"

# ----------------------------------------------------------


def print_ko_case(test_name, test_res, out_ko_case, val_ko_case):
    if test_res:
        print(f"{COLOR_DICT[RED]}"
              "#########################################")
        print("#####            KO CASE            #####")
        print("#########################################"
              f"{COLOR_DICT['end']}")

        with open(f'ko_case_{test_name}.txt', 'w') as f:
            if len(out_ko_case):
                print(f'[OUTPUT KO CASE OF : {test_name}]')
                f.write(f'[OUTPUT KO CASE OF : {test_name}]\n')
                for ko in out_ko_case:
                    print(ko)
                    f.write(f'{ko}\n')

            if len(val_ko_case):
                print(f'[LEAK or FD KO CASE OF : {test_name}]')
                f.write(f'[LEAK or FD KO CASE OF : {test_name}]\n')
                for ko in val_ko_case:
                    print(ko)
                    f.write(f'{ko}\n')


def test(test_name, test_input_list, status_only):
    try:
        with open(BASH_INIT_FILE, "w") as init_file:
            init_file.write(f'PS1="{BASH_PROMPT_PREFIX} "')

        test_res = 0
        print(f' ========================= TEST : [{test_name} {" STATUS ONLY" if status_only else ""}] ========================= ')

        output_res, out_ko_case = output_test(test_input_list, status_only)
        test_res |= output_res

        val_res, val_ko_case = valgrind_test(test_input_list)
        test_res |= val_res
        print()

        if os.path.isfile(f'ko_case_{test_name}.txt'):
            os.remove(f'ko_case_{test_name}.txt')
        print_ko_case(test_name, test_res, out_ko_case, val_ko_case)
        print()

    finally:
        if os.path.exists(BASH_INIT_FILE):
            os.remove(BASH_INIT_FILE)

    return test_res

