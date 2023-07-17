from test_function.test_functions import test


def main():
    test_res = 0
    echo_test = ["export A1=a1",
                 "env | grep -v ^_ | sort",  # tmp
                 "export B1=b1 B2=b2",
                 "env | grep -v ^_ | sort",  # tmp
                 "export A1+=a1",
                 "export A2+=a2",
                 "env | grep -v ^_ | sort",  # tmp
                 "export C1=c1 C1 C1=",
                 "export _",
                 "export _=",
                 "export _=aaaa",
                 "export __=bbbb",
                 "export OK1=ok1 -NG=ng OK2=ok2",
                 "env | grep -v ^_ | sort",  # tmp
                #  "export -option KEU=value", # bash print usage
                 "env | grep -v ^_ | sort",  # tmp
                 "unset A1",
                 ]

    test_res |= test("ft_export", echo_test, False)

    return test_res


if __name__ == '__main__':
    main()
