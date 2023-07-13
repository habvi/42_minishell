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

    not_pass_yet_paren_error_test = [
                    "(",
                    "((",
                    "(((",
                    "((((",
                    ")",
                    "))",
                    ")))",
                    "))))",
                    "())",
                    "(()",
                    "((())",
                    "(()) echo a",
                    "echo a (())",
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

    test_res |= test("paren", pass_paren_error_test)
    # todo: on
    # test_res |= test("paren", not_pass_yet_paren_error_test)
    test_res |= test("paren", paren_test)

    return test_res


if __name__ == '__main__':
    main()
