from test_functions import test


def main():
    test_res = 0
    echo_test = ["echo",
                 "echo a",
                 "echo a b c",
                 "echo a        b        c",
                 "echo a echo b echo c",
                 "echo aaaaaaaaaaaaaaaa bbbbbbbb  ccccccc echo   aa",
                 "echo /bin/echo a b c   d   e",
                 # "echo a \"\" b",
                 # "echo a \"\" \"\" \"\" b",
                 # "echo \"\"",
                 "echo -n hello",
                 "echo -n hello -n",
                 "echo -----n hello",
                 "echo -n -----n hello",
                 "echo -n -n -n -n -n  a  b  c",
                 "echo -n -n -n -n -n  a  b  c -n -n -n -m  d e f",
                 "echo -n -m hoge",
                 "echo - -n a b c",
                 "echo -n - -n a   b   c",
                 "echo -nnnnnnnnnnnnnnnnnnnnn a   b   c",
                 "echo -nnnnnnnnnmnnnnnnnnnnn a   b   c",
                 "echo -nnnnnn -n -n -n -nnnnnn a  -n -n -n   b",
                 "echo 123 456 -n  a b c  d",
                 "echo -N a b c",
                 "echo -n- a b c",
                 "echo n- a b c",
                 "echo -n-n a b c",
                 "echo nnnnnnn  -n a b c",
                 "echo nnnn- a b c",
                 ]

    test_res |= test("ft_echo", echo_test)

    return test_res


if __name__ == '__main__':
    main()
