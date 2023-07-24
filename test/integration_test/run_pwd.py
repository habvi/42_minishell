from test_function.test_functions import test

MKDIR = "rm -rf test_dir \n mkdir test_dir \n cd test_dir"
RMDIR = "cd .. \n chmod 777 test_dir \n rm -rf test_dir"
PATH_ADD = "export PATH+=:$PWD"

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
    ]  # todo: add more test after implement cd

    pwd_rm_test = [
        f"{PATH_ADD}\n __SHELL \n pwd",
        f"{PATH_ADD}\n{MKDIR} && chmod 000 $PWD \n pwd                    \n __SHELL__ \n pwd \n exit \n {RMDIR}",
        f"{PATH_ADD}\n{MKDIR} && chmod 000 $PWD \n pwd \n export PWD=xxxx \n __SHELL__ \n pwd \n exit \n {RMDIR}",
        f"{PATH_ADD}\n{MKDIR} && chmod 000 $PWD \n pwd \n unset PWD       \n __SHELL__ \n pwd \n exit \n {RMDIR}",
    ]


    # test_res |= test("ft_pwd", pwd_test, False, False)
    test_res |= test("ft_pwd with rm", pwd_rm_test, False, True)

    return test_res


if __name__ == '__main__':
    main()
