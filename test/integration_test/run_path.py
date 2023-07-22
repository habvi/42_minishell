from test_function.test_functions import test


def main():

    # CMD = "echo hello>f\ncat -e f\n/bin/cat f\n/bin/rm -rf f\n"
    CMD = "echo hello>f\n/bin/cat f\n/bin/rm -rf f\n"

    SCRIPT = "/bin/rm -rf hello.sh && echo '#!/bin/bash'>hello.sh && echo 'echo hello world'>>hello.sh && /bin/chmod +x hello.sh\n"\
            "/bin/rm -rf test_dir\n /bin/mkdir test_dir test_dir/dir1 test_dir/dir2\n"\
            "/bin/cp hello.sh test_dir/dir1\n"\
            "echo 'echo xxxxx'>>hello.sh && /bin/mv hello.sh test_dir/dir2\n"\
            "echo dir1 && /bin/ls test_dir/dir1\necho dir2 && /bin/ls test_dir/dir2\n"
    RMSCRIPT = "/bin/rm -rf test_dir && /bin/rm -rf hello.sh"
    STATUS = "echo $?"

    test_res = 0
    path_test = [
        f"{CMD}",
        f"export PATH=/bin\n{CMD}",
        f"export PATH=/bin:$PATH\n{CMD}",
        f"export PATH=::::$PATH\n{CMD}",
        f"export PATH=\n{CMD}",
        f"export PATH=:\n{CMD}",
        f"export PATH=::::\n{CMD}",
        f"export PATH=xxx\n{CMD}",
        f"export PATH=xxx:/bin\n{CMD}",
        f"export PATH=xxx:/bin::xxx\n{CMD}",
        f"unset PATH\n{CMD}",
        f"..\n{STATUS}\n...\n{STATUS}",
        f"export PATH=\n..\n{STATUS}\n...\n{STATUS}",
        f"export PATH=xxx\n..\n{STATUS}\n...\n{STATUS}",
        f"unset PATH\n..\n{STATUS}\n...\n{STATUS}",
        f"./a\n{STATUS}",
        f"a\n{STATUS}",
        f"a/\n{STATUS}",
        f"/bin\n{STATUS}",
        f"./bin\n{STATUS}"
        f"unset PATH\n./a\n{STATUS}",
        f"unset PATH\na\n{STATUS}",
        f"unset PATH\na/\n{STATUS}",
        f"unset PATH\n/bin\n{STATUS}",
        f"unset PATH\n./bin\n{STATUS}",
        f"{SCRIPT}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd test_dir/test_dir1\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n{RMSCRIPT}"
        f"unset PATH\nexport PATH=$PWD/test_dir/dir2:$PWD/test_dir/dir1\n{SCRIPT}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd test_dir/dir1\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n{RMSCRIPT}",
        f"unset PATH\n{SCRIPT}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd test_dir/dir1\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n{RMSCRIPT}",
        f"unset PATH\n{SCRIPT}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/cp test_dir/dir1/hello.sh ./\necho 'echo yyyyy'>>hello.sh\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n\n{RMSCRIPT}",
    ]

    test_res |= test("path", path_test, False)

    return test_res


if __name__ == '__main__':
    main()
