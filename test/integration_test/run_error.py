from test_function.test_functions import test
from test_function.print_ng_case import print_ng_cases

def run():
    test_res = 0

    syntax_err = [
                # "\"\"",
                #   "\'\'",
                #   "|",
                #   "||",
                  "&&",
                  # "echo a |",
                  # "echo a | echo b |",
                  "| echo a",
                  # "echo a || echo b ||",
                  # "echo a && echo b ||",
                  "&&"
                  "&&&"
                  "&&&&",
                  # "<<<<<<",
                  # "<< << <<",
                  # "<< >>",
                  # "<><>",
                  "<|"
                  "<||"
                  "<|||"
                  # "<&&"
                  # "<&&&"
                  # "<|echo a",
                  "<&&&"
                  "<|echo a",

                  # ">|",
                  # ">&&",
                  # ">||"
                  # "|<",
                  ]

    exec_err = ["'\"'",
                "\"'\"",
                "/",
                "/bin",
                "///////"
                ]

    error_test = syntax_err + exec_err

    test_res |= test("error", error_test, False, False)

    return test_res


def main():
    test_res = run()

    print_ng_cases(test_res)

    exit(test_res)


if __name__ == '__main__':
    main()
