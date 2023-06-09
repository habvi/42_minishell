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
                    "< nosuchfile <",
                    "< |",
                    "< nosuchfile &&",
                    "< nosuchfile && < nosuchfile",
                    "< nosuchfile && nosuchfile1 <",
                    "nosuchfile < && nosuchfile1 <",
                    "nosuchfile < && < nosuchfile1",
                    "< nosuchfile && < nosuchfile1 < nosuchfile2",
                    ]

    redirects_out_error_test = [

                    ]

    redirects_in_test =[
                    "echo aa >test_infile1 && echo bb > test_infile2",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1",
                    "cat test_infile1 && cat test_infille2 && cat < test_infile1",
                    "cat test_infile1 && cat test_infille2 && cat <     test_infile1",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1 && cat<test_infile1",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1 && cat<test_infile2",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1 || cat<test_infile1",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1 || cat<test_infile2",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1 | cat<test_infile2",
                    "cat test_infile1 && cat test_infille2 && cat<test_infile1 | cat <test_infile2",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1 | cat <test_infile2 | cat",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1 | cat <test_infile2 | cat | cat",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1 <test_infile2 | cat",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile1 <test_infile1 | cat",
                    "cat test_infile1 && cat test_infille2 && cat <test_infile2 | cat <test_infile2 <test_infile1 | cat | cat",
                    "cat test_infile1 && cat test_infille2 && cat <    test_infile1<test_infile2 | cat",
                    "cat test_infile1 && cat test_infille2 && <test_infile1 | cat",
                    "cat test_infile1 && cat test_infille2 && <test_infile1 | cat | grep nothing",
                    "cat test_infile1 && cat test_infille2 && <test_infile1 | cat | grep a",
                    "cat test_infile1 && cat test_infille2 && <test_infile1 <test_infile2 | cat",
                    "rm -f test_infile1 && rm -f test_infile1 && rm -f test_infile2"
                    ]

    redirects_out_test = [
                    "echo aa >test_outfile1 && cat test_outfile1",
                    "echo bb > test_outfile1 && cat test_outfile1",
                    "echo cc >            test_outfile1 && cat test_outfile1",
                    "echo dd >test_outfile1 && cat test_outfile1 && cat test_outfile1",
                    "echo ee >test_outfile1 || cat test_outfile1 && cat test_outfile1",
                    "echo ff >test_outfile1 | cat test_outfile1 && cat test_outfile1",
                    "echo gg >test_outfile1 | echo hh >test_outfile2 && cat test_outfile1 && cat test_outfile2",
                    "echo ii >test_outfile1 | echo jj >test_outfile2 | cat && cat test_outfile1 && cat test_outfile2",
                    "echo kk >test_outfile1 | echo ll >test_outfile2 | cat | cat && cat test_outfile1 && cat test_outfile2",
                    "echo mm >test_outfile1 < test_outfile2 | cat && cat test_outfile1 && cat test_outfile2",
                    "echo nn >    test_outfile1 <test_outfile2 | cat && cat test_outfile1 && cat test_outfile2",
                    ">test_outfile1 echo oo | cat && cat test_outfile1",
                    ">test_outfile1 >test_outfile2     echo pp | cat && cat test_outfile1 && cat test_outfile2",
                    "rm -f test_outfile1 && rm -f test_outfile1 && rm -f test_outfile2"
                    ]

    redirects_append_test = [
        
                    ]

    redirects_heredoc_test = [
        
                    ]

    # test_res |= test("redirect_in_error", redirects_in_error_test)
    # test_res |= test("redirect_out_error", redirects_out_error_test)
    test_res |= test("redirect_in", redirects_in_test)
    test_res |= test("redirect_out", redirects_out_test)
    # test_res |= test("redirect_out", redirects_append_test)
    # test_res |= test("redirect_out", redirects_heredoc_test)

    return test_res


if __name__ == '__main__':
    main()
