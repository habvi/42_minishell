from test_function.print_ng_case import print_ng_cases
import run_echo
import run_env
import run_exit
import run_export
import run_pwd
import run_cd
import run_declare

def run():
    test_res = 0

    test_res |= run_cd.main()
    test_res |= run_declare.main()
    test_res |= run_echo.main()
    test_res |= run_env.main()
    test_res |= run_exit.main()
    test_res |= run_export.main()
    test_res |= run_pwd.main()
    # test_res |= run_unset.main()

    return test_res


def main():
    test_res = run()

    print_ng_cases(test_res)

    exit(test_res)


if __name__ == '__main__':
    main()
