from test_function.test_functions import test
from itertools import permutations


def wildcard():
    DIR_NAME = "test_wildcard"
    MAKE_TEST_DIR = f"mkdir -p test_wildcard && cd {DIR_NAME} && "
    WORDS = "abb**x"
    random_files = ""
    for per in permutations(WORDS):
        random_files += ''.join(per) + " "
    random_files = random_files.replace("x", "'*'")
    TOUCH_TEST_FILES = f"{MAKE_TEST_DIR} touch {random_files} \n "
    SORT_COMPARE = f" | tr ' ' '\\n' | sort && cd ../ && rm -rf {DIR_NAME}"

    wildcard_test = [
                    f"echo * {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo ** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo ******* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * * {SORT_COMPARE}",

                    f"{TOUCH_TEST_FILES} echo a* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *a {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *a* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **a* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *a** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **a** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *nosuch {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo nosuch* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *nosuch* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **nosuch* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *nosuch** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **nosuch** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * a* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo a* * {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo a* *a {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * a* *a {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * a* *nosuch *a {SORT_COMPARE}",

                    f"{TOUCH_TEST_FILES} echo b* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *b {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *b* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **b* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *b** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **b** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * b* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo b* * {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo b* *b {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * b* *b {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * b* *nosuch *b {SORT_COMPARE}",

                    f"{TOUCH_TEST_FILES} echo ab* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo ba* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo ab** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo ba** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo a*b {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo b*a {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo b**a {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *ab {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *ba {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **ab {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **ba {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *ab* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **ab* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *ab** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo **ab** {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *a*b {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *b*a {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo a*b* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo b*a* {SORT_COMPARE}",

                    f"{TOUCH_TEST_FILES} echo * *a b* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *a b* * {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo b* *a* *b {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * b* *b *ab {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo * b* *nosuch a*b* *b {SORT_COMPARE}",

                    f"{TOUCH_TEST_FILES} echo '*'* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *'*' {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *'*'* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *'*'a* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *a'*'* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *'*'b* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *b'*'* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo *b'*'b* {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo '*'*'*' {SORT_COMPARE}",
                    f"{TOUCH_TEST_FILES} echo '*'*'*'* {SORT_COMPARE}",
                    ]

    return wildcard_test


def main():

    wildcard_test = wildcard()

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

    word_splitting_test = [

                    ]

    test_res = 0

    test_res |= test("wildcard", wildcard_test, False, False)
    test_res |= test("expansion", expansion_test, False, False)
    # test_res |= test("word_splitting", word_splitting_test, False, False)

    return test_res


if __name__ == '__main__':
    main()
