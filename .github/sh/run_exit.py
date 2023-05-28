from test_functions import test


def main():
    test_res = 0
    exit_test = ["exit",
                 "exit 0",
                 "exit 1",
                 "exit 42",
                 "exit -1",
                 "exit 2147483647",
                 "exit -2147483648",
                 "exit 9223372036854775807",
                 "exit -9223372036854775808",
                 "exit 0000000000000000000",
                 "exit 0000000000000000001",
                 # "exit \"  +42 \"",
                 "exit 1 1",
                 "exit -1 1",
                 "exit 1 1 1",
                 "exit 9223372036854775808",
                 "exit a",
                 "exit a b",
                 "exit a b c",
                 "exit a 1 b",
                 "exit a 1 1",
                 "exit a b 1",
                 "exit --1",
                 "exit -1+",
                 "exit -1+ a",
                 "exit -1+ 1",
                 "exit 9999999999999999999999999999999999999999999999999999999999999999",
                 "exit \t42",
                 "exit \n42",
                 "exit \v42",
                 "exit \f42",
                 # "exit \r42",
                 # "exit \r\r42",
                 ]  # add more test after update tokenizer

    test_res |= test("ft_exit", exit_test)
    exit(test_res)


if __name__ == '__main__':
    main()
