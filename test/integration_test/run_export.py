from test_functions import test

# todo : add exit at last, because bash prints exit shell exit, minishell does not implement now
PRINT_CMD = "unset PS1 && export | grep -v ^_ | grep -v SHLVL | grep -v PS1 | grep -v MAKE_TERMERR | grep -v MAKE_TERMOUT"
PRINT_EXIT_CMD = PRINT_CMD + " && exit"

def main():
    test_res = 0
    echo_test = [
        f"export A1=a1 \n {PRINT_EXIT_CMD}",
        f"export A1=a1 A1 A1+=a2\n {PRINT_EXIT_CMD}",
        f"export A1 A1+=a1 \n {PRINT_EXIT_CMD}",
        f"export A1=a1 A1+= \n {PRINT_EXIT_CMD}",
        f"export A1=a1 A1= \n {PRINT_EXIT_CMD}",
        f"export A1=a1 \n export A1+=a2 \n {PRINT_EXIT_CMD}",
        f"export A1=a1 \n export A1+=$A1 \n {PRINT_EXIT_CMD}",
        f"export OK1=ok1 NG1++ OK2 OK3=ok3$OK1 OK4=$OK1 OK5=\"$OK1\" \n {PRINT_EXIT_CMD}",
        f"export NG1~ ng*ngngngng \n {PRINT_EXIT_CMD}",
        f"export LC_COLLATE=C && export a* \n {PRINT_EXIT_CMD}",
        f"export LC_COLLATE=C && export * \n {PRINT_EXIT_CMD}",
        # f"export A=\"a   b   c\" \n echo $A \n echo \"$A\" {PRINT_EXIT_CMD}", # bug PS1
        # f"export A=\"a   b   c\" \n export B=$A     \n echo $B \n echo \"$B\" \n {PRINT_EXIT_CMD}", # word splitting
        f"export A=\"a   b   c\" \n export B=\"$A\" \n echo $B \n echo \"$B\" \n {PRINT_EXIT_CMD}",
        f"export A=\"a   b   c\"'d   e' \n export B=\"$A\" \n echo $B \n echo \"$B\" \n {PRINT_EXIT_CMD}",
    ]

    test_res |= test("ft_export", echo_test, False)

    return test_res


if __name__ == '__main__':
    main()
