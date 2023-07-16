from test_functions import test


def main():
    test_res = 0

    mix_error_test = [
                    "(echo a )|()",
                    "( echo a )|( )",
                    "( echo a ) | ()",
                    "( echo a ) | ( )",
                    "export A=A && echo $A && export A=B && echo $A",
                    "echo nothing | echo a && echo b",
                    "( echo a ) ( )",
                    "( echo a ) echo b",
                    "echo a && ( echo b ) || echo c",
                    ]

    different_result_from_bash_test = [
                    "&",
                    "&&&",
                    "& &",
                    "a &&",
                    "echo a & &&",
                    "echo a |",
                    "echo a ||",
                    "~a",
                    "echo $-",
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
                    ]

    subshell_test = [
                    "( echo a )",
                    "( echo a ) | cat",
                    "( ( echo a ) )",
                    "( ( echo a ) ) | cat",
                    "( ( echo a ) | /cat ) | cat",
                    "( ( ( echo a ) | /cat ) | cat )",
                    "( echo a ) | cat",
                    "( ( ls ) )",
                    "( ( ls) ) | cat",
                    "( ( ls ) )",
                    "( ( ls ) ) | cat",
                    "( (ls ) | /cat ) | cat",
                    "( ( ( ls ) | /cat ) | cat )",
                    "( pwd )",
                    "( ls ) | ( ( cat ) )",
                    "( cd libft && pwd )",
                    "( cd libft && pwd ) | cat",
                    "( cd libft && pwd ) && pwd",
                    "( ( cd libft && pwd ) | cd includes ) && pwd",
                    "( ( ( ls ) | cat ) | cat ) && pwd",
                    ]

    # test_res |= test("mix", mix_error_test)
    # test_res |= test("different", different_result_from_bash_test)
    test_res |= test("subshell", subshell_test, False)

    return test_res


if __name__ == '__main__':
    main()
