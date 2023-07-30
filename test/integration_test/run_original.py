from test_function.test_functions import test
from test_function.print_ng_case import print_ng_cases


def run():
    test_res = 0

    different_result_from_bash_test = [
                    # "&",
                    "&&&",
                    # "& &",
                    "a &&",
                    "echo a & &&",
                    "echo a |",
                    "echo a ||",
                    "~a",
                    "$-",
                    "echo $-",
                    # "$_",
                    "echo $_",
                    # "export -a",
                    # "(())",
                    # "((()))",
                    "(()())",
                    # "((()()))",
                    "<<a () <<b",
                    "<<a ||| <<b",
                    "echo a | (e) >a && a ||",
                    "$$",
                    "$$$",
                    # redirect in
                    "echo aa >test_infile1 && echo bb > test_infile2",
                    "cat test_infile1 && cat test_infille2 && <test_infile1 | cat | grep a",
                    "rm -f test_infile1 && rm -f test_infile1 && rm -f test_infile2",
                    # redirect out
                    "echo aa >test_outfile1 && cat test_outfile1",
                    "echo ff >test_outfile1 | cat test_outfile1 && cat test_outfile1",
                    "rm -f test_outfile1 && rm -f test_outfile1 && rm -f test_outfile2",
                    ] # todo more test

    # only status check
    test_res |= test("different", different_result_from_bash_test, True, False)

    return test_res


def main():
    test_res = run()

    print_ng_cases(test_res)

    exit(test_res)


if __name__ == '__main__':
    main()
