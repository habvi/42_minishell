from test_function.test_functions import test


def main():
    test_res = 0

    mix_error_test = [
                    "(echo a )|()",
                    "( echo a )|( )",
                    "( echo a ) | ()",
                    "( echo a ) | ( )",
                    "export A=A && echo $A && export A=B && echo $A",
                    # "echo nothing | echo a && echo b",
                    "( echo a ) ( )",
                    "( echo a ) echo b",
                    "echo a && ( echo b ) || echo c",
                    "( ls | )",
                    "( ls && )",
                    "( ls || )",
                    "( | ls )",
                    "( && ls )",
                    "( || ls )",
                    "( ls | | )",
                    "( ls | && )",
                    "( ls | || )",
                    "( | | ls )",
                    "( && && ls )",
                    "( || || ls )",
                    "( ls | echo a | )",
                    "( ls | echo a && )",
                    "( ls | echo a | ( echo b ) | )",
                    "( ls | ) | ( echo a | echo b )",
                    "( ls | ) && ( echo a | echo b )",
                    "( echo a | echo b ) | ( ls | )",
                    "( echo a | echo b ) && ( ls | )",
                    "( echo a | echo b ) | ( ls | ) | ( echo c )",
                    "( echo a | echo b ) && ( ls | ) | ( echo c )",
                    "( echo a | echo b ) | ( ls | ) && ( echo c )",
                    "( echo a | echo b ) && ( ls | ) && ( echo c )",
                    # bash error in pase..? minishell error in token
                    # "( ls | ) (",
                    # "( ls && ) (",
                    # "( ls || ) (",
                    ]

    subshell_test = [
                    "( echo a )",
                    "( echo a ) | cat",
                    "( ( echo a ) )",
                    "( ( echo a ) ) | cat",
                    "( ( echo a ) | cat ) | cat",
                    "( ( ( echo a ) | cat ) | cat )",
                    "( echo a ) | cat",
                    "( ( ls ) )",
                    "( ( ls) ) | cat",
                    "( ( ls ) )",
                    "( ( ls ) ) | cat",
                    "( (ls ) | cat ) | cat",
                    "( ( ( ls ) | cat ) | cat )",
                    "( pwd )",
                    "( ls ) | ( ( cat ) )",
                    "( cd libft && pwd )",
                    "( cd libft && pwd ) | cat",
                    "( cd libft && pwd ) && pwd",
                    "( ( cd libft && pwd ) | cd includes ) && pwd",
                    "( ( ( ls ) | cat ) | cat ) && pwd",
                    ]

    test_res |= test("mix", mix_error_test, False, False)
    test_res |= test("subshell", subshell_test, False, False)

    return test_res


if __name__ == '__main__':
    main()
