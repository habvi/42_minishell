from test_functions import test


def main():
    test_res = 0
    different_result_from_bash_test = [
                    "&",
                    "&&&",
                    "& &",
                    "a &&",
                    "echo a & &&",
                    "echo a |",
                    "echo a ||",
                    "~a",
                    "$-",
                    "echo $-",
                    "$_",
                    "echo $_",
                    "export -a",
                    "(())",
                    "((()))",
                    "(()())",
                    "((()()))",
                    "<< aaa",
                    "<<a () <<b",
                    "<<a ||| <<b",
                    "echo a | (e) >a && a ||",
                    "$$",
                    "$$$",
                    "$_",
                    ] # todo more test

    test_res |= test("different", different_result_from_bash_test, False)

    return test_res


if __name__ == '__main__':
    main()
