from itertools import combinations
from test_functions import test

DISPLAY_CMD = "declare -p | /bin/grep PWD | /bin/grep -v _="

def main():
    test_res = 0
    declare_test = [
        "declare | /bin/grep PWD | /bin/grep -v _=",
        f"{DISPLAY_CMD}",
        f"declare PWD=aaa \n {DISPLAY_CMD}",
        f"declare PWD=aaa \n declare -x PWD \n {DISPLAY_CMD}",
        f"declare PWD=aaa \n declare +x PWD \n {DISPLAY_CMD}",
        f"declare +x PWD=aaa \n {DISPLAY_CMD}",
        f"declare -x PWD=aaa \n {DISPLAY_CMD}",
        f"unset PWD \n declare PWD=aaa \n {DISPLAY_CMD}",
        f"unset PWD \n declare -x PWD=aaa \n {DISPLAY_CMD}",
        f"unset PWD \n declare +x PWD=aaa \n {DISPLAY_CMD}",
        f"unset PWD \n declare +x PWD \n {DISPLAY_CMD}",
        f"unset PWD \n declare -x PWD \n {DISPLAY_CMD}",
    ]

    test_res |= test("ft_declare", declare_test)

    return test_res


if __name__ == '__main__':
    main()
