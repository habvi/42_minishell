from itertools import combinations
from test_function.test_functions import test

DISPLAY_CMD = "declare -p | /bin/grep PWD | /bin/grep -v _="
STATUS = "\n echo $? \n"

RM_CWD_AND_CD_PRE = f"rm -rf testdir \n mkdir testdirA testdirA/testdirB \n cd testdirA/testdirB {STATUS} pwd \n rm -rf ../../testdirA \n {DISPLAY_CMD} \n"
STATUS_PWD_DISPLAY = f"{STATUS} pwd \n {DISPLAY_CMD} \n"
REGISTER_PATH = "export PATH=$PATH:$PWD \n"

def make_comb(base_list):
    comb_list = []
    for i in range(len(base_list) + 1):
        for p in combinations(base_list, i):
            comb_list.append(p)
    return comb_list

def append_cmd(cmds, cmd):
    if cmd:
        for c in cmd:
            cmds.append(c)
            cmds.append("\n")
    return cmds

def main():

    UNSET = ["unset PWD",
            "unset OLDPWD"]
    unset_comb = make_comb(UNSET)

    CD = ["cd ~"]
    cd_comb = make_comb(CD)

    EXPORT = ["export PWD",
            "export OLDPWD"]
    export_comb = make_comb(EXPORT)

    DISPLAY = ["export | /bin/grep PWD"]

    commands_list = []
    for unset in unset_comb:
        for cd in cd_comb:
            for export in export_comb:
                cmds = []
                cmds = append_cmd(cmds, DISPLAY)
                cmds = append_cmd(cmds, unset)
                cmds = append_cmd(cmds, cd)
                cmds = append_cmd(cmds, export)
                cmds = append_cmd(cmds, DISPLAY)
                commands_list.append("".join(cmds))

    additional_test = [
        f"cd {STATUS_PWD_DISPLAY}",
        f"cd ~ {STATUS_PWD_DISPLAY}",
        f"cd ~~ {STATUS_PWD_DISPLAY}",
        f"cd - {STATUS_PWD_DISPLAY}",
        f"cd -- {STATUS_PWD_DISPLAY}",
        f"cd --- {STATUS_PWD_DISPLAY}",
        f"cd -x /bin {STATUS_PWD_DISPLAY}",
        f"cd -xx /bin {STATUS_PWD_DISPLAY}",
        f"cd -xy /bin {STATUS_PWD_DISPLAY}",
        f"cd -x -x /bin {STATUS_PWD_DISPLAY}",
        f"cd -x -xx /bin {STATUS_PWD_DISPLAY}",
        f"cd -- /bin {STATUS_PWD_DISPLAY}",
        f"cd -x -- /bin {STATUS_PWD_DISPLAY}",
        f"cd -- -x /bin {STATUS_PWD_DISPLAY}",
        f"cd -- nothing {STATUS_PWD_DISPLAY}",
        f"cd -- nothing /bin {STATUS_PWD_DISPLAY}",
        f"cd nothing -- {STATUS_PWD_DISPLAY}",
        f"cd nothing {STATUS_PWD_DISPLAY}",
        f"cd nothing1 nothing2 {STATUS_PWD_DISPLAY}",
        f"cd nothing1 /bin {STATUS_PWD_DISPLAY}",
        f"cd /bin nothing1 {STATUS_PWD_DISPLAY}",
        f"cd /bin {STATUS} pwd {STATUS} cd - {STATUS_PWD_DISPLAY}",
        f"cd .. {STATUS} cd ../ {STATUS_PWD_DISPLAY}",
        f"pwd {STATUS} cd ../.././../.././../../../../../ {STATUS} pwd {STATUS} cd ../ {STATUS_PWD_DISPLAY}",
        f"unset PWD OLDPWD {STATUS} cd - {STATUS} cd ~ {STATUS_PWD_DISPLAY}",
        f"export PWD=aaaa {STATUS} cd ~ {STATUS_PWD_DISPLAY}",
        f"cd . {STATUS_PWD_DISPLAY}",
        f"cd / {STATUS_PWD_DISPLAY}",
        f"cd // {STATUS_PWD_DISPLAY}",
        f"cd /// {STATUS_PWD_DISPLAY}",
        f"cd //// {STATUS_PWD_DISPLAY}",
        f"cd ./././ {STATUS_PWD_DISPLAY}",
        f"cd .///////// {STATUS_PWD_DISPLAY}",
        f"cd ////////////////./././././../././. {STATUS_PWD_DISPLAY}",
        f"rm -rf testdir \n mkdir testdir \n cd testdir {STATUS} pwd \n cd ../ {STATUS} rmdir testdir \n cd - {STATUS_PWD_DISPLAY}",
        f"declare +x PWD OLDPWD \n cd .. {STATUS} cd /bin {STATUS} pwd \n cd - {STATUS} cd ~ {STATUS_PWD_DISPLAY} unset PWD \n export PWD \n cd - {STATUS} cd - {STATUS_PWD_DISPLAY}",
        f"rm -rf testdir \n mkdir testdir \n cd testdir \n pwd \n chmod 000 ../testdir {STATUS_PWD_DISPLAY} cd ../ {STATUS_PWD_DISPLAY} chmod 777 testdir \n rmdir testdir",
        f"rm -rf testdir \n mkdir testdir \n cd testdir \n pwd \n rmdir ../testdir {STATUS_PWD_DISPLAY} cd ../ {STATUS_PWD_DISPLAY} chmod 777 testdir \n rmdir testdir"]

    # rm cwd && cd
    rm_cwd_test = [
        f"{RM_CWD_AND_CD_PRE} cd nosuchdir {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /nosuchdir {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /nosuchdir/ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ../../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /../../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /../.. {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ../../../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /../../../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /../../.. {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd . {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd .. {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ... {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd .... {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ./../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /./../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /./.. {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ./.../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /./.../ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /./... {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ./../nosuchdir {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ../nosuchdir {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd - {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ~ {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd / {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd // {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /// {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd //// {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd /. {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd //. {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd //.. {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd //... {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ../testdirB {STATUS_PWD_DISPLAY}",
        f"{RM_CWD_AND_CD_PRE} cd ../../testdirA {STATUS_PWD_DISPLAY}"
    ]

    # rm cwd \n ./minishell \n pwd \n cd ./
    shell_in_rm_cwd_test = [
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd nosuchdir {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd nosuchdir {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /nosuchdir {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /nosuchdir/ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ../../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /../../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /../.. {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ../../../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /../../../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /../../.. {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd . {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd .. {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ... {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd .... {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ./../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /./../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /./.. {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ./.../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /./.../ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /./... {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ./../nosuchdir {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ../nosuchdir {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd - {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ~ {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd / {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd // {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /// {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd //// {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd /. {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd //. {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd //.. {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd //... {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ../testdirB {STATUS_PWD_DISPLAY}",
        f"{REGISTER_PATH} {RM_CWD_AND_CD_PRE} __SHELL__ \n cd ../../testdirA {STATUS_PWD_DISPLAY}",
    ]
    

    commands_list += additional_test
    # for c in commands_list:
    #     print(c)
    #     print("----------------")

    # todo: CDPATH test
    cdpath_test = [
        
                    ]

    test_res = 0

#     test_res |= test("cdpath", cdpath_test, False)
    test_res |= test("ft_cd", commands_list, False)
    test_res |= test("ft_cd rm_cwd", rm_cwd_test, False)
    test_res |= test("ft_cd shell_in_rm_cwd", shell_in_rm_cwd_test, True)

    return test_res


if __name__ == '__main__':
    main()
