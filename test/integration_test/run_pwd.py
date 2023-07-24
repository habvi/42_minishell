from test_function.test_functions import test

MKDIR = "rm -rf test_dir \n mkdir test_dir \n cd test_dir"
RMDIR = "cd .. \n chmod 777 test_dir \n rm -rf test_dir"
PATH_ADD = "export PATH+=:$PWD"
PWD = "echo 'pwd: '\n pwd \necho status: \"$?\"\n declare -p | grep PWD"
SHELL_PWD = f"__SHELL__\n {PWD}"

def main():

    test_res = 0
    pwd_test = [
        "pwd",
        "pwd a b c",
        "pwd 1 2 3",
        "pwd pwd",
        "cd - && pwd",
        "cd libft && pwd",
        "cd libft/ && pwd",
        "cd /libft && pwd",
        "cd /libft/ && pwd",
        f"{MKDIR}\n chmod 000 $PWD && pwd\n {RMDIR}",
        # "mkdir -p testdir && cd testdir && rmdir $PWD && pwd && chmod 775 $PWD",
        f"{MKDIR}\n chmod -r $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -w $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -x $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -rw $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -rx $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -wx $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -rwx $PWD && pwd\n {RMDIR}",
        "cd / && pwd",
        "cd // && pwd",
        "cd /// && pwd",
    ]  # todo: add more test after implement cd

    pwd_rm_test = [
        f"{PATH_ADD}\n {SHELL_PWD}",
        f"{PATH_ADD}\n export PWD=xxxx  \n {SHELL_PWD}",
        f"{PATH_ADD}\n unset PWD        \n {SHELL_PWD}",

        f"{PATH_ADD}\n cd / \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n cd // \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n cd /// \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n cd {'/'*50} \n {PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n cd / \n {PWD} \n export PWD=zzzzzz\n {SHELL_PWD}",
        f"{PATH_ADD}\n cd // \n {PWD} \n export PWD=zzzzzz\n {SHELL_PWD}",
        f"{PATH_ADD}\n cd /// \n {PWD} \n export PWD=zzzzzz\n {SHELL_PWD}",
        f"{PATH_ADD}\n cd {'/'*50} \n {PWD} \n export PWD=zzzzzz\n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && chmod 000 $PWD \n {PWD}                    \n {SHELL_PWD} \n {RMDIR}",
        f"{PATH_ADD}\n{MKDIR} && chmod 000 $PWD \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n {RMDIR}",
        f"{PATH_ADD}\n{MKDIR} && chmod 000 $PWD \n {PWD} \n unset PWD       \n {SHELL_PWD} \n {RMDIR}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd . \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd . \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd . \n {PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd .. \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd .. \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd .. \n {PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd / \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd / \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd / \n {PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd // \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd // \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd // \n {PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd /// \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd /// \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd /// \n {PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd {'../' * 20} \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd {'../' * 20} \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd {'../' * 20} \n {PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd nothing \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd nothing \n {PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd nothing \n {PWD}",


        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd . \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd . \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd . \n {PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd .. \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd .. \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd .. \n {PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd / \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd / \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd / \n {PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd // \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd // \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd // \n {PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd /// \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd /// \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd /// \n {PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd {'../' * 20} \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd {'../' * 20} \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd {'../' * 20} \n {PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD}                    \n {SHELL_PWD} \n cd nothing \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd nothing \n {PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {PWD} \n unset PWD       \n {SHELL_PWD} \n cd nothing \n {PWD} \n __SHELL__ \n {PWD}",

        f"{PATH_ADD}\n {SHELL_PWD * 10}",
        f"{PATH_ADD}\n export PWD=xxxx  \n {SHELL_PWD * 10}",
        f"{PATH_ADD}\n unset PWD        \n {SHELL_PWD * 10}",
        f"{PATH_ADD}\n export PWD=xxxx  \n {SHELL_PWD * 10}\n export PWD=yyyy \n {SHELL_PWD * 10}",
        f"{PATH_ADD}\n export PWD=xxxx  \n {SHELL_PWD * 10}\n unset PWD \n {SHELL_PWD * 10}",
    ]

    test_res |= test("ft_pwd", pwd_test, False, False)
    test_res |= test("ft_pwd with rm", pwd_rm_test, False, True)

    return test_res


if __name__ == '__main__':
    main()
