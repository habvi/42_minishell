from test_functions import test


def main():

    test_res = 0
    pwd_test = [
                "pwd",
                "pwd a b c",
                "pwd 1 2 3",
                "pwd pwd",
                 ]  # add more test after implement cd

    test_res |= test("ft_exit", pwd_test)

    return test_res


if __name__ == '__main__':
    main()
