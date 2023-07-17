from test_functions import test


def main():
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
                  "<< << <<",
                  "<< >>",
                  # "<><>",
                  "<|"
                  "<||"
                  "<|||"
                  # "<&&"
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

    test_res |= test("error", error_test, False)

    return test_res


if __name__ == '__main__':
    main()
