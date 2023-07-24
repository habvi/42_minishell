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

    test_res |= test("ft_pwd", pwd_test, False, False)

    return test_res


if __name__ == '__main__':
    main()
