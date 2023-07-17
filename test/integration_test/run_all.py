import glob

import run_builtin
import run_pipe
import run_op
import run_error
import run_original


BLUE = "\x1b[34m"
RESET = "\x1b[0m"


def print_test_title(title):
    print(BLUE)
    print(" " + "*" * (len(title) * 9 + 1) + " ")
    print(" *" + " " * len(title) * 4 + title + " " * len(title) * 4 + "* ")
    print(" " + "*" * (len(title) * 9 + 1) + " ")
    print(RESET)


def print_ng_cases(test_res):
    if not test_res:
        return

    for file in glob.glob('ko_case_*_cmd.txt'):
        with open(file, 'r') as f:
            print(f.read())
    return


def main():
    test_res = 0

    print_test_title("BUILTIN")
    test_res |= run_builtin.main()

    print_test_title("EXECUTION")
    test_res |= run_pipe.main()

    print_test_title("OPERATION")
    test_res |= run_op.main()

    print_test_title("ERROR")
    test_res |= run_error.main()

    # print_test_title("ORIGINAL")
    # test_res |= run_original.main()

    print_ng_cases(test_res)

    exit(test_res)


if __name__ == '__main__':
    main()
