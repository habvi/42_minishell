from test_functions import test


def main():
    test_res = 0
    pipe_test = ["/bin/ls -l",
                 "/bin/echo abcde",
                 "/bin/echo aaa bbb\n/bin/ls",
                 "/bin/echo aa\n/bin/echo bb\n/bin/echo ccc",
                 "/bin/echo aaa | /bin/grep a",
                 "/bin/echo aaa | /bin/cat -e",
                 "/bin/echo aaa | nothing",
                 ]

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
    # test_res |= test("multi_pipe", pipe_test)
    test_res |= test("multi_pipe", pipe_error_test, False)

    # stdin = "/bin/echo -e aaa\naacc\nbbb\nbbcc\nccc\naabb\nabc | /bin/grep a | /bin/grep c"
    # m_res, b_res = run_both(stdin)
    # put_result(val, m_res, b_res)

    # stdin = "/bin/cat | /bin/ls"
    # m_res, b_res = run_both(stdin)
    # put_result(val, m_res, b_res)

    # stdin = "abcde"
    # 'cat | echo -e "aaa\\naacc\\nbbb\\nbbcc\\nccc\\naabb\\nabc" | grep a | grep c'

    # stdin = "aa\nbb\ncc\nbbaa\n"
    # "cat | cat | cat | grep b"

    return test_res


if __name__ == '__main__':
    main()
