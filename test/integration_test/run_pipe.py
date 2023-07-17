from test_function.test_functions import test


def main():
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

    # todo: test on
    test_res |= test("multi_pipe", pipe_test, False)
    test_res |= test("multi_pipe", pipe_error_test, False)

    # stdin = "echo -e aaa\naacc\nbbb\nbbcc\nccc\naabb\nabc | grep a | grep c"
    # m_res, b_res = run_both(stdin)
    # put_result(val, m_res, b_res)

    # stdin = "cat | ls"
    # m_res, b_res = run_both(stdin)
    # put_result(val, m_res, b_res)

    # stdin = "abcde"
    # 'cat | echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c'

    # stdin = "aa\nbb\ncc\nbbaa\n"
    # "cat | cat | cat | grep b"

    return test_res


if __name__ == '__main__':
    main()
