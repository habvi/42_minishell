from test_functions import test


def main():
    test_res = 0
    pass_paren_error_test = [
                    "()",
                    "( )",
                    "( () )",
                    "( ( ) )",
                    "() echo a",
                    "( ) echo a",
                    "( ( ) ) echo a",
                    "echo a ()",
                    "echo a ( )",
                    "echo a ( ( ) )",
                    "echo a () ( ) echo b",
                    "echo a ( ) () echo b",
                    "echo a () () echo b",
                    "echo a ( ) ( ) echo b"
                    ]

    paren_test = [
                "(echo abc)",
                "(echo a b c)",
                "( (echo a) )",
                "( echo a b c )",
                "( ( echo a ) )",
                "( (echo a b c) )",
                "( ( echo a b c ) )",
                ]

    not_pass_yet_paren_error_test = [
                    # "(",
                    # "((",
                    # "(((",
                    # "((((",
                    ")",
                    "))",
                    ")))",
                    "))))",
                    "())",
                    # "(()",
                    # "((())",
                    # "(()) echo a",
                    "echo a (())",
                    ]


    test_res |= test("paren", pass_paren_error_test)
    test_res |= test("paren", paren_test)
    test_res |= test("paren", not_pass_yet_paren_error_test)

    return test_res


if __name__ == '__main__':
    main()
