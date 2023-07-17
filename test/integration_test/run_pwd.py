from test_functions import test


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
                "mkdir -p testdir && cd testdir && chmod 000 $PWD && pwd && chmod 775 $PWD",
                # "mkdir -p testdir && cd testdir && rmdir $PWD && pwd && chmod 775 $PWD",
                 ]  # todo: add more test after implement cd

    test_res |= test("ft_pwd", pwd_test, False)

    return test_res


if __name__ == '__main__':
    main()
