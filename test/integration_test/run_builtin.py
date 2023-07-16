import run_echo
import run_exit
import run_export
import run_pwd
import run_cd
import run_declare

def main():
    test_res = 0

    test_res |= run_cd.main()
    test_res |= run_declare.main()
    test_res |= run_echo.main()
    # test_res |= run_env.main()
    test_res |= run_exit.main()
    test_res |= run_export.main()
    test_res |= run_pwd.main()
    # test_res |= run_unset.main()

    return test_res


if __name__ == '__main__':
    main()
