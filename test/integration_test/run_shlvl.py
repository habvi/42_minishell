from test_function.test_functions import test
from test_function.print_ng_case import print_ng_cases


PATH_ADD = "export PATH+=:$PWD"


def main():
    test_res = 0

    lvl_list = ["0", "1", "255",
                "998", "999", "1000", "1001",
                "2147483645", "2147483646", "2147483647",
                "4294967295",
                "9223372036854775807", "9223372036854775808",
                "-1", "-2", "-999", "-1000",
                "-2147483646", "-2147483647", "-2147483648",
                "-9223372034707292161", "-9223372034707292162", "-9223372034707292163",
                "-9223372036854774807", "-9223372036854774808", "-9223372036854774809",
                "-9223372036854774810", "-9223372036854774811",
                "-9223372036854775806", "-9223372036854775807", "-9223372036854775808", "-9223372036854775809",
                "", "a", "++2", "+++++++++2", "--2", "+2+"
                ]


    shlvl_test = [
        "echo $SHLVL"
         ]

    for lvl in lvl_list:
        shlvl_test.append(f"{PATH_ADD}\necho init:$SHLVL\nexport SHLVL={str(lvl)}\necho before:$SHLVL\n__SHELL__\necho after:$SHLVL")

    test_res |= test("shlvl", shlvl_test, False, True)

    print_ng_cases(test_res)

    return test_res


if __name__ == '__main__':
    main()
