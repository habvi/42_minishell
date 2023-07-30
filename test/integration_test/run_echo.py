from test_function.test_functions import test


def main():
    test_res = 0

    echo_normal_test = [
        "echo $$",
         "echo a",
         "echo a b c",
         "echo a        b        c",
         "echo a echo b echo c",
         "echo aaaaaaaaaaaaaaaa bbbbbbbb  ccccccc echo   aa",
         "echo /bin/echo a b c   d   e",
         # "echo a \"\" b",
         # "echo a \"\" \"\" \"\" b",
         # "echo \"\"",
         "echo -n",
         "echo -n hello",
         "echo -n hello -n",
         "echo -----n hello",
         "echo -n -----n hello",
         "echo -n -n -n -n -n  a  b  c",
         "echo -n -n -n -n -n  a  b  c -n -n -n -m  d e f",
         "echo -n -m hoge",
         "echo - -n a b c",
         "echo -n - -n a   b   c",
         "echo -nnnnnnnnnnnnnnnnnnnnn a   b   c",
         "echo -nnnnnnnnnmnnnnnnnnnnn a   b   c",
         "echo -nnnnnn -n -n -n -nnnnnn a  -n -n -n   b",
         "echo 123 456 -n  a b c  d",
         "echo -N a b c",
         "echo -n- a b c",
         "echo n- a b c",
         "echo -n-n a b c",
         "echo nnnnnnn  -n a b c",
         "echo nnnn- a b c",
         # "echo 12345678901234567890123456789012345678901234567890123456789012",
         # "echo 123456789012345678901234567890123456789012345678901234567890123",
         # "echo 9999999999999999999999999999999999999999999999999999999999999999",
         # "echo 1234567890123456789012345678901234567890123456789012345678901234\n",
         # "echo 12345678901234567890123456789012345678901234567890123456789012345\n",
         # "echo 12345678901234567890123456789012345678901234567890123456789012345",   # subprocess.stderr NG?
         # "echo 12345678901234567890123456789012345678901234567890123456789012345 ",
         # "echo 123456789012345678901234567890123456789012345678901234567890123456",
         # "echo 1234567890123456789012345678901234567890123456789012345678901234567",
         # "echo 12345678901234567890123456789012345678901234567890123456789012345678",
        "echo a\tb\tc",
        "echo a\t\t\tb\t\t\tc",
        "echo a\t \t \tb\t  \t  \tc",
        "echo -n a\tb\tc",
        "echo -n a\t\t\tb\t\t\tc",
        "echo -n a\t \t \tb\t  \t  \tc",
        f"echo {'-n' * 100} a  b  c",
        # f"echo {'-n' * 1000} a  b  c",
        # f"echo {'-n' * 10000} a  b  c",
        # f"echo {'-n' * 100000} a  b  c",
        # f"echo {'-n' * 100000}m a  b  c",
        # f"echo {'-n' * 100000} a -n b  c",
        "echo a   b   c  \"|\"  A   B  C",
        "echo a   b   c  \"&&\"  A   B  C",
        "echo a   b   c  \"<<eof\"  A   B  C",
        "echo a   b   c  echo  A   B  C",
        "echo a   b   c  echo -n -n A   B  C",
        "e'c'ho a   b   c  echo -n -n A   B  C",
        "echo '-n' \"-n\" a  b  c",
        "echo '-''n' a  b  c",
        "echo '-'\"n\"nnnnnn a  b  c",
        "export N_OP=-nnnnnnnnn \n echo $N_OP a  b  c",
        "export N_OP=-nnnnnnnnn \n echo '$N_OP' a  b  c",
        "export N_OP=-nnnnnnnnn \n echo \"$N_OP\" a  b  c",
        "export N_OP=-nnnnnnnnn \n echo $N_OP$NOP a  b  c",
        "export N=nnnnnnnnn \n echo -$N$N a  b  c",
        "export N=nnnnnnnnn \n echo '-'$N$N a $N b  c",
        # f"echo {'ab   c ' * 1000}"
        # f"echo {'ab   c ' * 10000}"
    ]

    KEY_HOME = "$HOME"
    KEY_USER = "$USER"
    KEY_NOTHING = "$nothing"
    KEY_LONG = "A"*10
    VALUE_LONG = "B"*10

    echo_expand_test = [
        f"echo {KEY_HOME}",
        f"echo {KEY_HOME * 10}",
        f"echo {KEY_HOME * 100}",
        f"echo {KEY_HOME * 1000}",
        f"echo -n {KEY_HOME * 100}",
        f"echo -n {KEY_HOME * 10}{KEY_NOTHING}{KEY_USER * 10}",
        f"echo {KEY_NOTHING}",
        f"echo {KEY_NOTHING * 10}",
        f"echo {KEY_NOTHING * 100}",
        f"echo {KEY_NOTHING * 1000}",
        f"echo -n {KEY_NOTHING * 100}",
        f"echo -n {KEY_NOTHING * 10}{KEY_NOTHING}{KEY_USER * 10}",

        f"echo \"{KEY_NOTHING}\"{KEY_HOME}",
        f"echo {KEY_HOME}\"{KEY_NOTHING}\"",
        f"echo {KEY_HOME}\"{KEY_NOTHING}\"{KEY_USER}",
        f"echo \"{KEY_NOTHING}\"{KEY_HOME}{KEY_USER}",
        f"echo \"{KEY_NOTHING}\"{KEY_HOME}\"{KEY_NOTHING}\"{KEY_USER}\"{KEY_NOTHING}\"",
        f"echo \'{KEY_NOTHING}\'{KEY_HOME}",

        f"echo -n \"{KEY_NOTHING}\"{KEY_HOME}",
        f"echo -n {KEY_HOME}\"{KEY_NOTHING}\"",
        f"echo -n {KEY_HOME}\"{KEY_NOTHING}\"{KEY_USER}",
        f"echo -n \"{KEY_NOTHING}\"{KEY_HOME}{KEY_USER}",
        f"echo -n \"{KEY_NOTHING}\"{KEY_HOME}\"{KEY_NOTHING}\"{KEY_USER}\"{KEY_NOTHING}\"",
        f"echo -n \'{KEY_NOTHING}\'{KEY_HOME}",


        f"echo {KEY_HOME}'{KEY_NOTHING}'",
        f"echo {KEY_HOME}'{KEY_NOTHING}'{KEY_USER}",
        f"echo '{KEY_NOTHING}'{KEY_HOME}{KEY_USER}",
        f"echo '{KEY_NOTHING}'{KEY_HOME}'{KEY_NOTHING}'{KEY_USER}'{KEY_NOTHING}'",

        f"echo -n {KEY_HOME}'{KEY_NOTHING}'",
        f"echo -n {KEY_HOME}'{KEY_NOTHING}'{KEY_USER}",
        f"echo -n '{KEY_NOTHING}'{KEY_HOME}{KEY_USER}",
        f"echo -n '{KEY_NOTHING}'{KEY_HOME}'{KEY_NOTHING}'{KEY_USER}'{KEY_NOTHING}'",

        f"echo {KEY_NOTHING}\"a\"b'c'{KEY_NOTHING} 'A'\"B\"C"
        f"echo ${KEY_LONG}\"a\"b'c'${KEY_LONG} 'A'\"B\"C"
        f"export {KEY_LONG}={VALUE_LONG} \n echo ${KEY_LONG}\"a\"b'c'${KEY_LONG} 'A'\"B\"C"
        f"export {KEY_LONG * 10}={VALUE_LONG * 10} \n echo ${KEY_LONG * 10}\"a\"b'c'${KEY_LONG * 10} 'A'\"B\"C"

        f"echo -n {KEY_NOTHING}\"a\"b'c'{KEY_NOTHING} 'A'\"B\"C"
        f"echo -n ${KEY_LONG}\"a\"b'c'${KEY_LONG} 'A'\"B\"C"
        f"export {KEY_LONG}={VALUE_LONG} \n echo -n ${KEY_LONG}\"a\"b'c'${KEY_LONG} 'A'\"B\"C"
        f"export {KEY_LONG * 10}={VALUE_LONG * 10} \n echo -n ${KEY_LONG * 10}\"a\"b'c'${KEY_LONG * 10} 'A'\"B\"C"
    ]

    echo_test = echo_normal_test + echo_expand_test
    test_res |= test("ft_echo", echo_test, False, False)
    return test_res


if __name__ == '__main__':
    main()
