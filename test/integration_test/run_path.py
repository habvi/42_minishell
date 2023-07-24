from test_function.test_functions import test


def main():

    # CMD = "echo hello>f\ncat -e f\n/bin/cat f\n/bin/rm -rf f\n"
    CMD = "echo hello>f\n/bin/cat f\n/bin/rm -rf f\n"

    MAKE_SCRIPT = "/bin/rm -f hello.sh && echo '#!/bin/bash'>hello.sh && echo -n 'echo hello world'>>hello.sh && /bin/chmod +x hello.sh\n"
    MKDIR = "/bin/rm -rf test_dir\n /bin/mkdir test_dir test_dir/dir1 test_dir/dir2\n"
    CP_SCRIPT_DIR0 = "/bin/cp hello.sh test_dir      \n echo ' drom test_dir'>>test_dir/hello.sh\n"
    CP_SCRIPT_DIR1 = "/bin/cp hello.sh test_dir/dir1 \n echo ' from test_dir/dir1'>>test_dir/dir1/hello.sh\n"
    CP_SCRIPT_DIR2 = "/bin/cp hello.sh test_dir/dir2 \n echo ' from test_dir/dir2'>>test_dir/dir2/hello.sh\n"
    ADD_SCRIPT = "echo ' from project root'>>hello.sh\n"

    LS_TEST_DIR = "/bin/ls -l test_dir && /bin/ls -lR test_dir\n"

    SCRIPT = MAKE_SCRIPT + MKDIR + CP_SCRIPT_DIR0 + CP_SCRIPT_DIR1 + CP_SCRIPT_DIR2 + ADD_SCRIPT

    PATH_ADD = "export PATH=$PWD/test_dir/dir2:$PWD/test_dir/dir1"

    RMSCRIPT = "/bin/chmod -R 777 test_dir && /bin/rm -rf test_dir \n /bin/rm -f hello.sh"
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


        # search path test
        f"{SCRIPT}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd test_dir/test_dir1\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n{RMSCRIPT}"
        f"{SCRIPT}\nunset PATH            \nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n{RMSCRIPT}",
        f"{SCRIPT}\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n{RMSCRIPT}",
        f"{SCRIPT}\nunset PATH            \ncd test_dir     \nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd ..   \n{RMSCRIPT}",
        f"{SCRIPT}\nunset PATH\n{PATH_ADD}\ncd test_dir     \nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd ..   \n{RMSCRIPT}",
        f"{SCRIPT}\nunset PATH            \ncd test_dir/dir1\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd ../..\n{RMSCRIPT}",
        f"{SCRIPT}\nunset PATH\n{PATH_ADD}\ncd test_dir/dir1\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd ../..\n{RMSCRIPT}",
        f"{SCRIPT}\nunset PATH            \ncd test_dir/dir1\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd ../..\n{RMSCRIPT}",
        f"{SCRIPT}\nunset PATH\n{PATH_ADD}\ncd test_dir/dir1\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\ncd ../..\n{RMSCRIPT}",

        # search path test with permission denied
        # test_dir : permission denied
        f"{SCRIPT}\n/bin/chmod -x test_dir\n            hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir\n            hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir\n            hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir\n            hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",


        # test_dir/dir1/hello.sh : permission denied
        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1/hello.sh\n           hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1/hello.sh\n           hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1/hello.sh\n           hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1/hello.sh\n           hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1/hello.sh\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1/hello.sh\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1/hello.sh\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1/hello.sh\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        # test_dir/dir2/hello.sh : permission denied
        f"{SCRIPT}\n/bin/chmod -x test_dir/dir2/hello.sh\n            hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir2/hello.sh\n            hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir2/hello.sh\n            hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir2/hello.sh\n            hello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir2/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir2/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir2/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir2/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir2/hello.sh\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir2/hello.sh\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir2/hello.sh\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir2/hello.sh\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        # test_dir/dir1/hello.sh && test_dir/dir2/hello.sh : permission denied
        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1/hello.sh test_dir/dir2/hello.sh\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1/hello.sh test_dir/dir2/hello.sh\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1/hello.sh test_dir/dir2/hello.sh\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1/hello.sh test_dir/dir2/hello.sh\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1/hello.sh test_dir/dir2/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1/hello.sh test_dir/dir2/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1/hello.sh test_dir/dir2/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1/hello.sh test_dir/dir2/hello.sh\nunset PATH\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1/hello.sh test_dir/dir2/hello.sh\n{LS_TEST_DIR}\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1/hello.sh test_dir/dir2/hello.sh\n{LS_TEST_DIR}\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1/hello.sh test_dir/dir2/hello.sh\n{LS_TEST_DIR}\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1/hello.sh test_dir/dir2/hello.sh\n{LS_TEST_DIR}\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",



        # test_dir/dir1 : permission denied
        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",


        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1\nunset PATH\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1\nunset PATH\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1\nunset PATH\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1\nunset PATH\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1\nunset PATH\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1\nunset PATH\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1\nunset PATH\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1\nunset PATH\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",


        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",



        # test_dir/dir2 : permission denied
        f"{SCRIPT}\n/bin/chmod -x test_dir/dir2\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir2\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir2\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir2\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir2\nhello.sh\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir2\nhello.sh\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir2\nhello.sh\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir2\nhello.sh\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",


        f"{SCRIPT}\n/bin/chmod -x test_dir/dir2\nunset PATH\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir2\nunset PATH\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir2\nunset PATH\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir2\nunset PATH\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir2\nunset PATH\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir2\nunset PATH\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir2\nunset PATH\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir2\nunset PATH\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",


        f"{SCRIPT}\n/bin/chmod -x test_dir/dir2\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir2\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir2\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir2\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir2\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir2\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir2\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir2\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",


        # test_dir/dir1 && test_dir/dir2 : permission denied
        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1 test_dir/dir2\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1 test_dir/dir2\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1 test_dir/dir2\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1 test_dir/dir2\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1 test_dir/dir2\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1 test_dir/dir2\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1 test_dir/dir2\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1 test_dir/dir2\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",


        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1 test_dir/dir2\nunset PATH\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1 test_dir/dir2\nunset PATH\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1 test_dir/dir2\nunset PATH\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1 test_dir/dir2\nunset PATH\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1 test_dir/dir2\nunset PATH\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1 test_dir/dir2\nunset PATH\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1 test_dir/dir2\nunset PATH\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1 test_dir/dir2\nunset PATH\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",


        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1 test_dir/dir2\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1 test_dir/dir2\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1 test_dir/dir2\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1 test_dir/dir2\nunset PATH\n{PATH_ADD}\nhello.sh\n{STATUS}\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

        f"{SCRIPT}\n/bin/chmod -x test_dir/dir1 test_dir/dir2\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -r test_dir/dir1 test_dir/dir2\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod -w test_dir/dir1 test_dir/dir2\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",
        f"{SCRIPT}\n/bin/chmod 000 test_dir/dir1 test_dir/dir2\nunset PATH\n{PATH_ADD}\n{STATUS}\n./hello.sh\n{STATUS}\n/bin/chmod -R 777 test_dir\n{RMSCRIPT}",

    ]

    test_res |= test("path", path_test, False, False)

    return test_res


if __name__ == '__main__':
    main()
