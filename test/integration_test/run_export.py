from test_functions import test

# PRINT_CMD = "export | grep -v ^_ | grep -v SHLVL | grep -v PS1 | grep -v MAKE_TERMERR | grep -v MAKE_TERMOUT | grep -v ^$ | tr -d \'\\\'"
PRINT_CMD = "export | grep -v ^_ | grep -v SHLVL | grep -v PS1 | grep -v MAKE_TERMERR | grep -v MAKE_TERMOUT"

def main():
    test_res = 0
    echo_test = ["export A1=a1",
                 PRINT_CMD,
                 "export B1=b1 B2=b2",
                 PRINT_CMD,
                 "export A1+=a1",
                 "export A2+=a2",
                 PRINT_CMD,
                 "export C1=c1 C1 C1=",
                 "export _",
                 "export _=",
                 "export _=aaaa",
                 "export __=bbbb",
                 "export OK1=ok1 -NG=ng OK2=ok2",
                 PRINT_CMD,
                 # "export -option KEU=value",
                 # PRINT_CMD,
                 ]

    test_res |= test("ft_export", echo_test)

    return test_res


if __name__ == '__main__':
    main()
