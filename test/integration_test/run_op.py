from test_function.print_ng_case import print_ng_cases
import run_and_or
import run_mix
import run_paren
import run_redirects
import run_expansion
import run_path

def main():
    test_res = 0

    test_res |= run_and_or.main()
    test_res |= run_mix.main()
    test_res |= run_paren.main()
    test_res |= run_redirects.main()
    test_res |= run_expansion.main()

    print_ng_cases(test_res)

    return test_res


if __name__ == '__main__':
    main()
