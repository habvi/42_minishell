import run_echo
import run_exit


def main():
    test_res = 0

    test_res |= run_echo.main()
    # test_res |= run_exit.main() //TODO: fix test

    return test_res


if __name__ == '__main__':
    main()
