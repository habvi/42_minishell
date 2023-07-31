from test_function.test_functions import test
from test_function.print_ng_case import print_ng_cases

def run():
    test_res = 0
    pipe_test = ["ls -l",
                 "echo abcde",
                 "echo aaa bbb\nls",
                 "echo aa\necho bb\necho ccc",
                 "echo aaa | grep a",
                 "echo aaa | cat -e",
                 "echo aaa | nothing",
                 ] # todo more test

    pipe_error_test = [
                    "|",
                    "| | ",
                    "| | |",
                    "echo a | | ",
                    "| echo a",
                    "| | echo a",
                    "echo a | |",
                    "| | echo a",
                    "echo a | | echo b"
                    ]

    test_res |= test("multi_pipe", pipe_test, False, False)
    test_res |= test("multi_pipe", pipe_error_test, False, False)

    return test_res


def main():
    test_res = run()

    print_ng_cases(test_res)

    exit(test_res)


if __name__ == '__main__':
    main()
