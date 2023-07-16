from test_functions import test


def main():
    test_res = 0

    word_splitting_test = [

                    ]

    wildcard_test = [

                    ]

    expansion_test = [
                    "$",
                    "$?",
                    "$??",
                    "$__",
                    "$HOME",
                    "\"$HOME\"",
                    "\'$HOME\'",
                    "echo $HOME",
                    "echo \"$HOME\"",
                    "echo \'$HOME\'",
                    "$HOME $HOME",
                    "echo $HOME$HOME",
                    "echo \"$HOME\"\"$HOME\"",
                    "echo \'$HOME\'\'$HOME\'",
                    "echo $HOME\"$HOME\"",
                    "echo \"$HOME\"$HOME",
                    "echo $HOME\'$HOME\'",
                    "echo \'$HOME\'$HOME",
                    "echo \'$HOME\'\"$HOME\"",
                    "echo \"$HOME\"\'$HOME\'",
                    "echo $HOME\'$HOME\'\"$HOME\"",
                    "echo $HOME\"$HOME\"\'$HOME\'",
                    "echo \'$HOME\'$HOME\"$HOME\"",
                    "echo \"$HOME\"$HOME\'$HOME\'",
                    "echo \'$HOME\'\"$HOME\"$HOME",
                    "echo \"$HOME\"\'$HOME\'$HOME",

                    "$PWD",
                    "echo $PWD",
                    "export TEST=libft && cd $TEST && pwd && unset TEST",
                    "export TEST=libft && cd \"$TEST\" && pwd && unset TEST",
                    "export TEST=libft && cd \'$TEST\' && pwd && unset TEST",
                    ]


    # test_res |= test("word_splitting", word_splitting_test)
    # test_res |= test("wildcard", wildcard_test)
    test_res |= test("expansion", expansion_test)

    return test_res


if __name__ == '__main__':
    main()
