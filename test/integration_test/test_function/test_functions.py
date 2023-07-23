import os
import sys
sys.path.append(os.path.join(os.path.dirname(__file__), '.'))

from test_output import output_test, BASH_INIT_FILE, BASH_PROMPT_PREFIX
from test_valgrind import valgrind_test
from color import RED, COLOR_DICT

STDOUT_IDX = 0
STDERR_IDX = 1
STATUS_IDX = 2
IS_EXITED_IDX = 3

# output test res
TEST_NO_IDX = 0
OK_IDX = 1
KO_IDX = 2
SKIP_IDX = 3


# ----------------------------------------------------------


def rm_outfile(test_name):
    if os.path.isfile(f'ko_case_{test_name}_cmd.txt'):
        os.remove(f'ko_case_{test_name}_cmd.txt')
    if os.path.isfile(f'ko_case_{test_name}_out.txt'):
        os.remove(f'ko_case_{test_name}_out.txt')


def save_ko_cmd(test_name, out_ko_case, val_ko_case):
    with open(f'ko_case_{test_name}_cmd.txt', 'w') as f:
        if len(out_ko_case):
            f.write(f'[OUTPUT KO CASE OF : {test_name}]\n')
            f.write(f'{"-" * 100}\n')
            for stdin, _, _ in out_ko_case:
                f.write(f'{stdin}\n')
                f.write(f'{"-" * 100}\n')

        if len(val_ko_case):
            f.write(f'[LEAK or FD KO CASE OF : {test_name}]\n')
            f.write(f'{"-" * 100}\n')
            for ko in val_ko_case:
                f.write(f'{ko}\n')
                f.write(f'{"-" * 100}\n')
            # for stdin, _, _ in val_ko_case:
            #     f.write(f'{stdin}\n')


def write_out_to_file(name, stdin, output_result, f):
    f.write(f'=== {name} ===')
    f.write(f' stdin  : [{stdin}]\n')
    f.write(f' stdout : [{output_result[STDOUT_IDX]}]\n')
    f.write(" stderr : [")

    for err_out in output_result[STDERR_IDX]:
        f.write(f'{err_out}\n')
    # for i in range(len(output_result[STDERR_IDX])):
    #     f.write(output_result[STDERR_IDX][i], end='')
    #     if i + 1 < len(output_result[STDERR_IDX]):
    #         f.write()
    f.write("]\n")
    f.write(f' status : {output_result[STATUS_IDX]}\n')
    f.write(f' exited : {output_result[IS_EXITED_IDX]}\n')
    f.write(f'\n')


# def write_val_to_f(name, stdin, output_result, f):
#
#     return


def save_ko_out(test_name, out_ko_case, val_ko_case):
    with open(f'ko_case_{test_name}_out.txt', 'w') as f:
        if len(out_ko_case):
            f.write(f'[OUTPUT KO CASE OF : {test_name}]\n')
            f.write(f'{"-" * 100}\n')
            for ko in out_ko_case:
                stdin, m_res, b_res = ko
                write_out_to_file("minishell", stdin, m_res, f)
                write_out_to_file("bash", stdin, b_res, f)
                f.write(f'{"-" * 100}\n')

        if len(val_ko_case):
            f.write(f'[LEAK or FD KO CASE OF : {test_name}]\n')
            f.write(f'{"-" * 100}\n')
            for ko in val_ko_case:
                f.write(ko)
                f.write(f'{"-" * 100}\n')
                # stdin, m_res, b_res = ko
                # write_val_to_f("minishell", stdin, m_res, f)
                # write_val_to_f("bash", stdin, b_res, f)


def save_ko_case(test_name, test_res, out_ko_case, val_ko_case):
    rm_outfile(test_name)

    if test_res == 0:
        return

    save_ko_cmd(test_name, out_ko_case, val_ko_case)
    save_ko_out(test_name, out_ko_case, val_ko_case)


def print_ko_case(test_name, test_res, out_ko_case, val_ko_case):
    if test_res == 0:
        return

    print(f"{COLOR_DICT[RED]}"
          "#########################################")
    print("#####            KO CASE            #####")
    print("#########################################"
          f"{COLOR_DICT['end']}")

    if len(out_ko_case):
        print(f'[OUTPUT KO CASE OF : {test_name}]')
        print('-' * 100)
        for stdin, _, _ in out_ko_case:
            print(stdin)
            print('-' * 100)

    if len(val_ko_case):
        print(f'[LEAK or FD KO CASE OF : {test_name}]')
        print('-' * 100)
        for ko in val_ko_case:
            print(ko)
            print('-' * 100)
    #     for stdin, _, _ in val_ko_case:
    #         print(stdin)


# ----------------------------------------------------------


def test(test_name, test_input_list, status_only, shell_replace):
    try:
        with open(BASH_INIT_FILE, "w") as init_file:
            init_file.write(f'PS1="{BASH_PROMPT_PREFIX} "')

        test_res = 0
        print(f' ========================= '
              f'TEST : [{test_name} {" STATUS ONLY" if status_only else ""}]'
              f' ========================= ')

        output_res, out_ko_case = output_test(test_input_list, status_only, shell_replace)
        test_res |= output_res

        val_res, val_ko_case = valgrind_test(test_input_list, shell_replace)
        test_res |= val_res
        print()

        print_ko_case(test_name,test_res,out_ko_case,val_ko_case)
        save_ko_case(test_name, test_res, out_ko_case, val_ko_case)
        print()


    finally:
        if os.path.exists(BASH_INIT_FILE):
            os.remove(BASH_INIT_FILE)

    return test_res

