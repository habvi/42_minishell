from test_functions import test


def main():
    test_res = 0
    env_test = [
                "env",
                "env -",
                "env --",
                "env -- -",
                "env -a",
                "env --a",
                "env -a b",
                ]

    # todo: self test? expect test?
    different_behavior_from_bash_test = [
                "env - -",
                "env -- --",
                "env - --",
                "env - a",
                "env a",
                "env a b",
                "env - -a",
                "env -- -a",
                ]

    test_res |= test("ft_env", env_test, True)
    # test_res |= test("ft_env original", different_behavior_from_bash_test, True)

    return test_res


if __name__ == '__main__':
    main()
