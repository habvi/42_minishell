from test_functions import test


def main():
    test_res = 0

    and_error_test = [
                    "&&",
                    "&& &&",
                    "&& && &&",
                    "a && &&",
                    "&& a",
                    "&& && a",
                    "a && &&",
                    "&& && a",
                    "a && && b",
                    "a && && b &&"
                    ]

    or_error_test = [
                    "||",
                    "|| ||",
                    "|| || ||",
                    "echo a || ||",
                    "|| echo a",
                    "|| || echo a",
                    "echo a || ||",
                    "|| || echo a",
                    "echo a || || echo b",
                    "echo a || || echo b ||",
                    ]

    and_test = ["echo a && echo b",
                "ls && echo a b c def && grep a",
                "ls && echo a b c def",
                "cd libft && pwd",
                "cd libft && pwd && cd - && pwd",
                "unset OLDPWD && cd -", # KO: exit status 0 -> 1
                "echo a && grep a",
                "ls && grep a",
                # "exit 1 && echo abc", # KO: print exit
                # "exit 2 && echo abc", # KO: print exit
                # "exit 1 && exit 2", # KO: print exit
                # "exit 2 && exit 5", # KO: print exit
                # "ls && exit 1 && echo abc", # KO: print exit
                # "ls && exit 2 && echo abc", # KO: print exit
                # "ls && exit 2 && exit 1", # KO: print exit
                # "ls && exit 2 && exit 8", # KO: print exit
                # "ls && exit 2 && exit 8 && echo abc", # KO: print exit
                "cd nosuchfile && echo a b",
                "cd nosuchfile && cat nosuchfile && echo a b",
                ]

    or_test = [
                "echo a || echo b",
                "ls || echo a b c def || grep a",
                "ls || echo a b c def",
                "cd libft || pwd",
                "cd libft || pwd || cd - || pwd",
                "unset OLDPWD || cd -",
                "echo a || grep a",
                "ls || grep a",
                # "exit 1 || echo abc", # KO: print exit
                # "exit 2 || echo abc", # KO: print exit
                # "exit 1 || exit 2", # KO: print exit
                # "exit 2 || exit 5", # KO: print exit
                # "ls || exit 1 || echo abc",
                # "ls || exit 2 || echo abc",
                # "ls || exit 2 || exit 1",
                # "ls || exit 2 || exit 8",
                # "ls || exit 2 || exit 8 || echo abc",
                "cd nosuchfile || echo a b",
                "cd nosuchfile || cat nosuchfile || echo a b",
                ]

    and_or_mix_test = [
                "echo a && echo b || echo c",
                "echo a || echo b && echo c",
                "ls && echo a b c def || grep a",
                "ls || echo a b c def && grep a",
                "cd libft || pwd || cd - && pwd",
                "cd libft || pwd && cd - || pwd",
                "cd libft || pwd && cd - && pwd",
                "cd libft && pwd || cd - && pwd",
                "cd libft && pwd || cd - || pwd",
                "cd libft && pwd && cd - || pwd",
                "echo a || echo b && grep a",
                "echo a && echo b || grep a",
                "ls || grep a && echo a",
                "ls && grep a || echo a",
                # "exit 1 && echo abc || ls", # KO: print exit
                # "exit 1 || echo abc && ls", # KO: print exit
                # "ls || exit 1 && echo abc",
                # "ls && exit 1 || echo abc", # KO: print exit
                # "ls || exit 2 && echo abc",
                # "ls && exit 2 || echo abc", # KO: print exit
                # "ls || exit 2 && exit 1", # KO: print exit
                # "ls && exit 2 || exit 1", # KO: print exit
                # "ls || exit 2 && exit 8", # KO: print exit
                # "ls && exit 2 || exit 8", # KO: print exit
                # "ls && exit 2 || exit 8 || echo abc", # KO: print exit
                # "ls || exit 2 && exit 8 || echo abc", # KO: print exit
                # "ls || exit 2 || exit 8 && echo abc",
                # "ls || exit 2 && exit 8 && echo abc", # KO: print exit
                # "ls && exit 2 && exit 8 || echo abc", # KO: print exit
                # "ls && exit 2 || exit 8 && echo abc", # KO: print exit
                "cd nosuchfile || echo a b && cd nosuchfile",
                "cd nosuchfile && echo a b || cd nosuchfile",
                ]

    test_res |= test("and_error", and_error_test)
    test_res |= test("or_error", or_error_test)
    test_res |= test("and", and_test)
    test_res |= test("or", or_test)
    test_res |= test("ans_or_mix", and_or_mix_test)

    return test_res


if __name__ == '__main__':
    main()
