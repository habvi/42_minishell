from test_function.test_functions import test

MKDIR = "rm -rf test_dir \n mkdir test_dir \n cd test_dir"
RMDIR = "cd .. \n chmod 777 test_dir \n rm -rf test_dir"
PATH_ADD = "export PATH+=:$PWD"
SHOW_PWD =              "\necho 'pwd: '          \n pwd \necho status: \"$?\"\n declare -p | grep PWD\n"
SHELL_PWD = "\n__SHELL__\n echo 'new shell pwd: '\n pwd \necho status: \"$?\"\n declare -p | grep PWD\n"

def main():

    test_res = 0
    pwd_test = [
        "pwd",
        "pwd a b c",
        "pwd 1 2 3",
        "pwd pwd",
        "cd - && pwd",
        "cd libft && pwd",
        "cd libft/ && pwd",
        "cd /libft && pwd",
        "cd /libft/ && pwd",
        f"{MKDIR}\n chmod 000 $PWD && pwd\n {RMDIR}",
        # "mkdir -p testdir && cd testdir && rmdir $PWD && pwd && chmod 775 $PWD",
        f"{MKDIR}\n chmod -r $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -w $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -x $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -rw $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -rx $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -wx $PWD && pwd\n {RMDIR}",
        f"{MKDIR}\n chmod -rwx $PWD && pwd\n {RMDIR}",
        "cd / && pwd",
        "cd // && pwd",
        "cd /// && pwd",
    ]  # todo: add more test after implement cd

    pwd_rm_test = [
        f"{PATH_ADD}\n {SHELL_PWD}",
        f"{PATH_ADD}\n export PWD=xxxx  \n {SHELL_PWD}",
        f"{PATH_ADD}\n unset PWD        \n {SHELL_PWD}",

        f"{PATH_ADD}\n cd / \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n cd // \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n cd /// \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n cd {'/'*50} \n {SHOW_PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n cd / \n {SHOW_PWD} \n export PWD=zzzzzz\n {SHELL_PWD}",
        f"{PATH_ADD}\n cd // \n {SHOW_PWD} \n export PWD=zzzzzz\n {SHELL_PWD}",
        f"{PATH_ADD}\n cd /// \n {SHOW_PWD} \n export PWD=zzzzzz\n {SHELL_PWD}",
        f"{PATH_ADD}\n cd {'/'*50} \n {SHOW_PWD} \n export PWD=zzzzzz\n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && chmod 000 $PWD \n {SHOW_PWD}                    \n {SHELL_PWD} \n {RMDIR}",
        f"{PATH_ADD}\n{MKDIR} && chmod 000 $PWD \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n {RMDIR}",
        f"{PATH_ADD}\n{MKDIR} && chmod 000 $PWD \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n {RMDIR}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd . \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd . \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd . \n {SHOW_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd .. \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd .. \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd .. \n {SHOW_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd / \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd / \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd / \n {SHOW_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd // \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd // \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd // \n {SHOW_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd /// \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd /// \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd /// \n {SHOW_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd {'../' * 20} \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd {'../' * 20} \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd {'../' * 20} \n {SHOW_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd nothing \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd nothing \n {SHOW_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd nothing \n {SHOW_PWD}",


        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd . \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd . \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd . \n {SHOW_PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd .. \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd .. \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd .. \n {SHOW_PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd / \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd / \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd / \n {SHOW_PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd // \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd // \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd // \n {SHOW_PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd /// \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd /// \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd /// \n {SHOW_PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd {'../' * 20} \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd {'../' * 20} \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd {'../' * 20} \n {SHOW_PWD} \n {SHELL_PWD}",

        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD}                    \n {SHELL_PWD} \n cd nothing \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n export PWD=xxxx \n {SHELL_PWD} \n cd nothing \n {SHOW_PWD} \n {SHELL_PWD}",
        f"{PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n unset PWD       \n {SHELL_PWD} \n cd nothing \n {SHOW_PWD} \n __SHELL__ \n {SHOW_PWD}",

        f"{PATH_ADD}\n {SHELL_PWD * 10}",
        f"{PATH_ADD}\n export PWD=xxxx  \n {SHELL_PWD * 10}",
        f"{PATH_ADD}\n unset PWD        \n {SHELL_PWD * 10}",
        f"{PATH_ADD}\n export PWD=xxxx  \n {SHELL_PWD * 10}\n export PWD=yyyy \n {SHELL_PWD * 10}",
        f"{PATH_ADD}\n export PWD=xxxx  \n {SHELL_PWD * 10}\n unset PWD \n {SHELL_PWD * 10}",


        f"echo 1-1-1 current        \n {PATH_ADD}\n                     {SHOW_PWD} ",
        f"echo 1-1-2 current        \n {PATH_ADD}\n unset  PWD       \n {SHOW_PWD} ",
        f"echo 1-1-3 current        \n {PATH_ADD}\n export PWD=xxxxx \n {SHOW_PWD} ",
        f"echo 1-1-4 current        \n {PATH_ADD}\n export PWD=$HOME \n {SHOW_PWD} ",
        f"echo 1-1-5 current        \n {PATH_ADD}\n export PWD=/     \n {SHOW_PWD} ",
        f"echo 1-1-6 current        \n {PATH_ADD}\n export PWD=//    \n {SHOW_PWD} ",
        f"echo 1-1-7 current        \n {PATH_ADD}\n export PWD=.     \n {SHOW_PWD} ",
        f"echo 1-1-8 current        \n {PATH_ADD}\n export PWD=..    \n {SHOW_PWD} ",
        f"echo 1-1-9 current        \n {PATH_ADD}\n export PWD=../.. \n {SHOW_PWD} ",
        f"echo 1-1-10 current        \n {PATH_ADD}\n export PWD=../../../../../ \n {SHOW_PWD} ",
        f"echo 1-1-11 current        \n {PATH_ADD}\n cd /             \n {SHOW_PWD} ",
        f"echo 1-1-12 current        \n {PATH_ADD}\n cd //            \n {SHOW_PWD} ",
        f"echo 1-1-13 current        \n {PATH_ADD}\n cd ///           \n {SHOW_PWD} ",
        f"echo 1-1-14 current        \n {PATH_ADD}\n cd .             \n {SHOW_PWD} ",
        f"echo 1-1-15 current        \n {PATH_ADD}\n cd ..            \n {SHOW_PWD} ",
        f"echo 1-1-16 current        \n {PATH_ADD}\n cd ../../        \n {SHOW_PWD} ",
        f"echo 1-1-17 current        \n {PATH_ADD}\n cd ../../../../../\n {SHOW_PWD} ",

        f"echo 1-1-12 current        \n {PATH_ADD}\n cd //            \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-13 current        \n {PATH_ADD}\n cd ///           \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-14 current        \n {PATH_ADD}\n cd .             \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-15 current        \n {PATH_ADD}\n cd ..            \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-16 current        \n {PATH_ADD}\n cd ../../        \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-17 current        \n {PATH_ADD}\n cd ../../../../../\n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",

        f"echo 1-1-11 current        \n {PATH_ADD}\n cd /             \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-12 current        \n {PATH_ADD}\n cd //            \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-13 current        \n {PATH_ADD}\n cd ///           \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-14 current        \n {PATH_ADD}\n cd .             \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-15 current        \n {PATH_ADD}\n cd ..            \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-16 current        \n {PATH_ADD}\n cd ../../        \n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-17 current        \n {PATH_ADD}\n cd ../../../../../\n export PWD=xxxxx \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",


        f"echo 1-1-11 current        \n {PATH_ADD}\n cd /             \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-12 current        \n {PATH_ADD}\n cd //            \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-13 current        \n {PATH_ADD}\n cd ///           \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-14 current        \n {PATH_ADD}\n cd .             \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-15 current        \n {PATH_ADD}\n cd ..            \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-16 current        \n {PATH_ADD}\n cd ../../        \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-17 current        \n {PATH_ADD}\n cd ../../../../../\n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",

        f"echo 1-1-11 current        \n {PATH_ADD}\n cd /             \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-12 current        \n {PATH_ADD}\n cd //            \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-13 current        \n {PATH_ADD}\n cd ///           \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-14 current        \n {PATH_ADD}\n cd .             \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-15 current        \n {PATH_ADD}\n cd ..            \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-16 current        \n {PATH_ADD}\n cd ../../        \n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",
        f"echo 1-1-17 current        \n {PATH_ADD}\n cd ../../../../../\n unset PWD \n {SHOW_PWD}\n __SHELL__ \n {SHOW_PWD} ",

        f"echo 1-2-1 current new    \n {PATH_ADD}\n                     {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-2-2 current new    \n {PATH_ADD}\n unset  PWD       \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-2-3 current new    \n {PATH_ADD}\n export PWD=xxxxx \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-2-4 current new    \n {PATH_ADD}\n export PWD=$HOME \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-2-5 current new    \n {PATH_ADD}\n export PWD=/     \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-2-6 current new    \n {PATH_ADD}\n export PWD=//    \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-2-7 current new    \n {PATH_ADD}\n export PWD=.     \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-2-8 current new    \n {PATH_ADD}\n export PWD=..    \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-2-9 current new    \n {PATH_ADD}\n export PWD=../.. \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-2-10 current new    \n {PATH_ADD}\n export PWD=../../../../../ \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-1-11 current new    \n {PATH_ADD}\n cd /             \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-1-12 current new    \n {PATH_ADD}\n cd //            \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-1-13 current new    \n {PATH_ADD}\n cd ///           \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-1-14 current new    \n {PATH_ADD}\n cd .             \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-1-15 current new    \n {PATH_ADD}\n cd ..            \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-1-16 current new    \n {PATH_ADD}\n cd ../../        \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 1-1-17 current new    \n {PATH_ADD}\n cd ../../../../../\n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",


        f"echo 2-2-1 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n                     {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-2-2 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n unset  PWD       \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-2-3 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n export PWD=xxxxx \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-2-4 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n export PWD=$HOME \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-2-5 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n export PWD=/     \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-2-6 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n export PWD=//    \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-2-7 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n export PWD=.     \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-2-8 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n export PWD=..    \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-2-9 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n export PWD=../.. \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-2-10 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n export PWD=../../../../../ \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-1-11 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n cd /             \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-1-12 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n cd //            \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-1-13 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n cd ///           \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-1-14 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n cd .             \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-1-15 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n cd ..            \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-1-16 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n cd ../../        \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-1-17 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n cd ../../../../../\n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 2-1-18 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n cd ../../../../../\n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",


        f"echo 3-2-1 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-2-2 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n unset  PWD       \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-2-3 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n export PWD=xxxxx \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-2-4 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n export PWD=$HOME \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-2-5 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n export PWD=/     \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-2-6 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n export PWD=//    \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-2-7 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n export PWD=.     \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-2-8 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n export PWD=..    \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-2-9 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n export PWD=../.. \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-2-10 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n export PWD=../../../../../ \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-1-11 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n cd /             \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-1-12 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n cd //            \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-1-13 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n cd ///           \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-1-14 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n cd .             \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-1-15 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n cd ..            \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-1-16 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n cd ../../        \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-1-17 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n cd ../../../../../\n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
        f"echo 3-1-18 current        \n {PATH_ADD}\n{MKDIR} && rm -rf ../test_dir \n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD} \n cd ../../../../../\n {SHOW_PWD} \n __SHELL__\n {SHOW_PWD}",
    ]

    test_res |= test("ft_pwd", pwd_test, False, False)
    test_res |= test("ft_pwd with rm", pwd_rm_test, False, True)

    return test_res


if __name__ == '__main__':
    main()
