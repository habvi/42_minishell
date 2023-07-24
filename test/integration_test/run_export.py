from test_function.test_functions import test

PRINT_CMD = "export | grep -v ^_ | grep -v PS1 | grep -v MAKE_TERMERR | grep -v MAKE_TERMOUT"
INIT = "unset LS_COLORS\n export PS1='bash '"

def main():
    test_res = 0
    export_test = [
        f"{INIT} \n export A1=a1 \n{PRINT_CMD}",
        f"{INIT} \n export A1=a1 A1 A1+=a \n{PRINT_CMD}",
        f"{INIT} \n export A1 A1+=a1 \n{PRINT_CMD}",
        f"{INIT} \n export A1=a1 A1+= \n{PRINT_CMD}",
        f"{INIT} \n export A1=a1 A1= \n{PRINT_CMD}",
        f"{INIT} \n export A1=a1 \n export A1+=a2 \n{PRINT_CMD}",
        f"{INIT} \n export A1=a1 \n export A1+=$A1 \n{PRINT_CMD}",
        f"{INIT} \n export OK1=ok1 NG1++ OK2 OK3=ok3$OK1 OK4=$OK1 OK5=\"$OK1\" \n{PRINT_CMD}",
        f"{INIT} \n export NG1~ ng*ngngngng \n{PRINT_CMD}",
        f"{INIT} \n export LC_COLLATE=C && export a* \n{PRINT_CMD}",
        f"{INIT} \n export LC_COLLATE=C && export * \n{PRINT_CMD}",
        f"{INIT} \n export A=\"a   b   c\" \n export B=\"$A\" \n echo $B \n echo \"$B\" \n{PRINT_CMD}",
        f"{INIT} \n export A=\"a   b   c\"'d   e' \n export B=\"$A\" \n echo $B \n echo \"$B\" \n{PRINT_CMD}",
        f"{INIT} \n export A=a B=b C=c D \n export A+=$A$B$noghint$C B=\"  \"aa$C\n {PRINT_CMD}",
    ]

    test_res |= test("ft_export", export_test, False, False)

    return test_res


if __name__ == '__main__':
    main()
