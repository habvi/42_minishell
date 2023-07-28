from test_function.test_functions import test
from test_function.print_ng_case import print_ng_cases

MKDIR = "rm -rf test_dir \n mkdir test_dir \n cd test_dir"
RMDIR = "cd .. \n rm -rf test_dir"
TOUCH_NG = "echo 'this is ng file' > ng \n chmod 000 ng"
RM_NG = "chmod 777 ng \n rm -f ng"

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
                    # "< nosuchfile &&", # original
                    "< nosuchfile && < nosuchfile",
                    "< nosuchfile && nosuchfile1 <",
                    "nosuchfile < && nosuchfile1 <",
                    "nosuchfile < && < nosuchfile1",
                    "< nosuchfile && < nosuchfile1 < nosuchfile2",
                    "cat -e < /dev/stdin\naaa\nbbb\nccc"
                    ] # todo more test

    redirects_out_error_test = [
                    ">",
                    "> >",
                    "> > >",
                    "nosuchfile >",
                    "> > nosuchfile",
                    "> nosuchfile >",
                    "> |",
                    # "> nosuchfile &&",
                    # "> nosuchfile && > nosuchfile",
                    # "> nosuchfile && nosuchfile1 >",
                    # "nosuchfile > && nosuchfile1 >",
                    # "nosuchfile > && > nosuchfile1",
                    # "> nosuchfile && > nosuchfile1 > nosuchfile2",
                    "echo hello >/dev/stdout",
                    "echo hello >/dev/stdout | cat -e",
                    "echo hello </dev/stdin | cat >/dev/stdout | cat -e"
                    ] # todo more test

    RMFILES = "rm -f test_infile1 && rm -f test_infile2"
    redirects_in_test =[
                    f"{RMFILES} \n echo aa >test_infile1 && echo bb > test_infile2 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat < test_infile1 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <     test_infile1 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 && cat<test_infile1 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 && cat<test_infile2 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 || cat<test_infile1 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 || cat<test_infile2 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 | cat<test_infile2 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat<test_infile1 | cat <test_infile2 && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 | cat <test_infile2 | cat && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 | cat <test_infile2 | cat | cat && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 <test_infile2 | cat && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile1 <test_infile1 | cat && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <test_infile2 | cat <test_infile2 <test_infile1 | cat | cat && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && cat <    test_infile1<test_infile2 | cat && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && <test_infile1 | cat && {RMFILES}",
                    f"cat test_infile1 && cat test_infille2 && <test_infile1 | cat | grep nothing && {RMFILES}",
                    # "cat test_infile1 && cat test_infille2 && <test_infile1 | cat | grep a", # for actions
                    f"cat test_infile1 && cat test_infille2 && <test_infile1 <test_infile2 | cat  && {RMFILES}",
                    # "rm -f test_infile1 && rm -f test_infile1 && rm -f test_infile2"
                    ]

    redirects_out_test = [
                    f"{RMFILES} \n echo aa >test_outfile1 && cat test_outfile1 && {RMFILES}",
                    f"echo bb > test_outfile1 && cat test_outfile1 && {RMFILES}",
                    f"echo cc >            test_outfile1 && cat test_outfile1 && {RMFILES}",
                    f"echo dd >test_outfile1 && cat test_outfile1 && cat test_outfile1 && {RMFILES}",
                    f"echo ee >test_outfile1 || cat test_outfile1 && cat test_outfile1 && {RMFILES}",
                    # "echo ff >test_outfile1 | cat test_outfile1 && cat test_outfile1", # for actions
                    f"echo gg >test_outfile1 | echo hh >test_outfile2 && cat test_outfile1 && cat test_outfile2 && {RMFILES}",
                    f"echo ii >test_outfile1 | echo jj >test_outfile2 | cat && cat test_outfile1 && cat test_outfile2 && {RMFILES}",
                    f"echo kk >test_outfile1 | echo ll >test_outfile2 | cat | cat && cat test_outfile1 && cat test_outfile2 && {RMFILES}",
                    f"echo mm >test_outfile1 < test_outfile2 | cat && cat test_outfile1 && cat test_outfile2 && {RMFILES}",
                    f"echo nn >    test_outfile1 <test_outfile2 | cat && cat test_outfile1 && cat test_outfile2 && {RMFILES}",
                    f">test_outfile1 echo oo | cat && cat test_outfile1 && {RMFILES}",
                    f">test_outfile1 >test_outfile2     echo pp | cat && cat test_outfile1 && cat test_outfile2 && {RMFILES}",
                    ]

    redirects_append_test = [
        "rm -f out \n echo a >> out \n cat out \n echo b >> out \n cat out \n rm -f out",
        "rm -f out \n echo a >> 'ou't \n cat out \n echo b >> out \n cat out \n rm -f out",
        "rm -f out \n export file=out\necho a >> $file \n cat out \n echo b >> out \n cat out \n rm -f out",
        "rm -f in out \n echo in>in \n echo a >> out \n cat <in >>out \n cat out \n rm -f in out",
        "rm -f in out1 out2 out3 nothing\n echo abc >out1>out2 <nothing >out3",
        "rm -f in out1 out2 out3 nothing\n echo abc >out1>out2 <nothing >out3 \n ls -l \n rm -f in out1 out2 out3",
        "rm -f in out1 out2 ng\n touch ng && chmod 000 ng\necho abc >out1>ng>out2 \n ls -l \n chmod 777 ng && rm -f in out1 out2 out3",
                    ] # todo more test

    BIG = "a" * 20

    redirects_heredoc_test = [
        "cat << eof \ntest1\ntest2\n$HOME\n\"$HOME\"\n'$HOME'\neof",
        "cat <<eof1<<eof2\neof11\neof\neof1\neof22\n$HOME$hoge$PWD\neof2\n",
        "rm -f out1 out2\ncat << eof>out1>out2 \ntest1\ntest2\n$HOME\n\"$HOME\"\n'$HOME'\neof\ncat out1\ncatou2\nrm -f out1 out2",
        "cat -e << 'eof' \ntest1\ntest2\n$HOME\n\"$HOME\"\n'$HOME'\neof",
        "cat -e << '' \ntest1\ntest2\n$HOME\n\"$HOME\"\n'$HOME'\n\'\'\n\"\"\n\n",
        "cat -e << \"\" \ntest1\ntest2\n$HOME\n\"$HOME\"\n'$HOME'\n\n",
        "cat << $HOME \ntest1\ntest2\n$HOMEee\n\"$HOME\"\n'$HOME'\n$HOME",
        "cat << '$HOME' \ntest1\ntest2\n$HOMEee\n\"$HOME\"\n'$HOME'\n$HOME",
        "cat << \"$HOME\" \ntest1\ntest2\n$HOMEee\n\"$HOME\"\n'$HOME'\n$HOME$USER$hoge $huga$PWD\n$HOME",
        "cat << $nothing \ntest1\n\ntest2\n$HOMEee\n\"$HOME\"\n'$HOME'\n$nothing",
        "cat -e << 'e'o\"f\" \ntest1\n\ntest2\n$?$HOME$?\n\"$HOME\"\n'$HOME'\neof",
        "cat << a\n$HOME\"\"\n\n        '$hoge'$hoge\n '\n\"\na",
        f"cat << eof | wc \n{BIG}\neof\n",
        "<no |<no <<eof <no cat -e && <<eof2 cat -e\ntest1\n$HOME\neof\ntest2\n$HOME\neof2\n",
        ]  # todo more test

    redirects_test_add = [
        f"{MKDIR} \n ls \n export f='a   b' \n echo aaa >$f     \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a   b' \n echo aaa >'$f'   \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a   b' \n echo aaa >\"$f\" \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a   b' \n echo aaa >out1>$f>out2     \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a   b' \n echo aaa >out1>'$f'>out2   \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a   b' \n echo aaa >out1>\"$f\">out2 \n ls \n {RMDIR}",

        f"{MKDIR} \n ls \n export f='   a' \n echo aaa >$f     \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='   a' \n echo aaa >'$f'   \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='   a' \n echo aaa >\"$f\" \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='   a' \n echo aaa >out1>$f>out2     \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='   a' \n echo aaa >out1>'$f'>out2   \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='   a' \n echo aaa >out1>\"$f\">out2 \n ls \n {RMDIR}",

        f"{MKDIR} \n ls \n export f='a    ' \n echo aaa >$f     \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a    ' \n echo aaa >'$f'   \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a    ' \n echo aaa >\"$f\" \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a    ' \n echo aaa >out1>$f>out2     \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a    ' \n echo aaa >out1>'$f'>out2   \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='a    ' \n echo aaa >out1>\"$f\">out2 \n ls \n {RMDIR}",

        f"{MKDIR} \n ls \n export f='     ' \n echo aaa >$f     \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='     ' \n echo aaa >'$f'   \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='     ' \n echo aaa >\"$f\" \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='     ' \n echo aaa >out1>$f>out2     \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='     ' \n echo aaa >out1>'$f'>out2   \n ls \n {RMDIR}",
        f"{MKDIR} \n ls \n export f='     ' \n echo aaa >out1>\"$f\">out2 \n ls \n {RMDIR}",


        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >ng >$f     \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >ng >'$f'   \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >ng >\"$f\" \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >ng >out1>$f>out2     \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >ng >out1>'$f'>out2   \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >ng >out1>\"$f\">out2 \n ls \n {RM_NG} \n {RMDIR}",

        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >$f >ng    \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >'$f'>ng   \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >\"$f\" >ng\n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >out1>$f>ng>out2     \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >out1>'$f'>ng>out2   \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n echo aaa >out1>\"$f\">ng>out2 \n ls \n {RM_NG} \n {RMDIR}",


        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat <ng >$f     \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat <ng >'$f'   \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat <ng >\"$f\" \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat <ng >out1>$f>out2     \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat <ng >out1>'$f'>out2   \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat <ng >out1>\"$f\">out2 \n ls \n {RM_NG} \n {RMDIR}",

        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat >$f <ng    \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat >'$f'<ng   \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat >\"$f\" <ng\n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat >out1>$f<ng>out2     \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat >out1>'$f'<ng>out2   \n ls \n {RM_NG} \n {RMDIR}",
        f"{MKDIR} \n ls \n {TOUCH_NG} \n export f='a   b' \n cat >out1>\"$f\"<ng>out2 \n ls \n {RM_NG} \n {RMDIR}",

        ]

    test_res |= test("redirect_in_error", redirects_in_error_test, False, False)
    test_res |= test("redirect_out_error", redirects_out_error_test, False, False)
    test_res |= test("redirect_in", redirects_in_test, False, False)
    test_res |= test("redirect_out", redirects_out_test, False, False)
    test_res |= test("redirect_append", redirects_append_test, False, False)
    test_res |= test("redirect_heredoc", redirects_heredoc_test, False, False)
    test_res |= test("redirect_additional_test", redirects_test_add, False, False)

    print_ng_cases(test_res)

    return test_res


if __name__ == '__main__':
    main()
