from itertools import combinations
from test_functions import test

DISPLAY_CMD = "declare -p | /bin/grep PWD | /bin/grep -v _="

def main():
    test_res = 0
    declare_test = [
        # "declare | /bin/grep PWD | /bin/grep -v _=",
        "declare -p | /bin/grep PWD | /bin/grep -v _=",
        "declare PWD=aaa\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
        "declare PWD=aaa\ndeclare -x PWD\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
        "declare PWD=aaa\ndeclare +x PWD\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
        "declare +x PWD=aaa\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
        "declare -x PWD=aaa\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
        "unset PWD\ndeclare PWD=aaa\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
        "unset PWD\ndeclare -x PWD=aaa\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
        "unset PWD\ndeclare +x PWD=aaa\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
        "unset PWD\ndeclare +x PWD\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
        "unset PWD\ndeclare -x PWD\ndeclare -p | /bin/grep PWD | /bin/grep -v _=",
    ]

    test_res |= test("ft_declare", declare_test, False)

    return test_res


if __name__ == '__main__':
    main()
