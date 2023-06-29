from itertools import combinations
from test_functions import test

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

    # for c in commands_list:
    #     print(c)
    #     print("----------------")

    test_res = test("ft_cd", commands_list)
    return test_res


if __name__ == '__main__':
    main()
