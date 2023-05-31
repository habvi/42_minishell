import run_builtin
import run_pipe


BLUE = "\x1b[34m"
RESET = "\x1b[0m"


def print_test_title(title):
    print(BLUE)
    print(" " + "*" * (len(title) * 9 + 1) + " ")
    print(" *" + " " * len(title) * 4 + title + " " * len(title) * 4 + "* ")
    print(" " + "*" * (len(title) * 9 + 1) + " ")
    print(RESET)


def main():
    test_res = 0

    print_test_title("BUILTIN")
    test_res |= run_builtin.main()

    print_test_title("EXECUTION")
    test_res |= run_pipe.main()

    exit(test_res)


if __name__ == '__main__':
    main()
