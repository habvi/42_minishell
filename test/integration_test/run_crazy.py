from test_function.test_functions import test


def main():

    command_list = []

    for i in range(256):
        if chr(i).isprintable():
            command_list.append(chr(i))

    test_res = 0
    test_res |= test("crazy", command_list, False)

    return test_res


if __name__ == '__main__':
    main()
