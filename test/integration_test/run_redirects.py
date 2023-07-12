from test_functions import test


def main():
    test_res = 0

    redirects_in_error_test = [
                    "<",
                    "< <",
                    "< < <",
                    "< nosuchfile",
                    "nosuchfile <",
                    "echo < nosuchfile",
                    "< < nosuchfile",
                    ]

    redirects_out_error_test = [

                    ]

    redirects_in_test = [

                    ]

    redirects_out_test = [

                    ]

    test_res |= test("redirect_in_error", redirects_in_error_test)
    # test_res |= test("redirect_out_error", redirects_out_error_test)
    # test_res |= test("redirect_in", redirects_in_test)
    # test_res |= test("redirect_out", redirects_out_test)


    return test_res


if __name__ == '__main__':
    main()
