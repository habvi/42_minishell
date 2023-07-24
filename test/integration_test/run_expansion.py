from test_function.test_functions import test

# for wildcard
DIR_NAME = "test_wildcard"
MAKE_TEST_DIR = f"mkdir -p test_wildcard && cd {DIR_NAME} && "
RANDOM_FILES = "z1 zz2 3z 4zz zz5z z6zz z7z7z z8zz8zz zz9z9zzz"
TOUCH_TEST_Z = f"{MAKE_TEST_DIR} touch {RANDOM_FILES}"
SORT_COMPARE = f" | tr ' ' '\\n' | sort && cd ../ && rm -rf {DIR_NAME}"

def main():
    test_res = 0

    word_splitting_test = [

                    ]

    wildcard_test = [
                    f"echo * | {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo * {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo z* {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo *z {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo *z* {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo **z* {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo *z** {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo **z** {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo *nosuch {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo nosuch* {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo *nosuch* {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo **nosuch* {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo *nosuch** {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo **nosuch** {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo * * {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo * z* {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo z* * {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo z* *z {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo * z* *z {SORT_COMPARE}",
                    f"{TOUCH_TEST_Z} echo * z* *nosuch *z {SORT_COMPARE}",
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
                    "cd $HOME && pwd",
                    "export TEST=libft && cd $TEST && pwd",
                    "export TEST=libft && cd \"$TEST\" && pwd",
                    "export TEST=libft && cd \'$TEST\' && pwd",
                    ] # todo more test


    # test_res |= test("word_splitting", word_splitting_test, False, False)
    test_res |= test("wildcard", wildcard_test, False, False)
    test_res |= test("expansion", expansion_test, False, False)

    return test_res


if __name__ == '__main__':
    main()
