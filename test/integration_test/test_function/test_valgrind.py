import shutil
import subprocess
from color import print_color_str, print_color_str_no_lf, RED, GREEN, YELLOW

# ----------------------------------------------------------
PATH_MINISHELL_LEAK = "./minishell"
PATH_BASH_LEAK = "bash"

# ----------------------------------------------------------

VALGRIND = "valgrind"
VALGRIND_OP = " --track-fds=yes "

# valgrind str
DEFINITELY = "definitely"
INDIRECTLY = "indirectly"
POSSIBLY = "possibly"
FD_FLAG = "DESCRIPTORS:"

# ----------------------------------------------------------

# valgrind test res
VAL_TEST_NO_IDX = 0
VAL_OK_IDX = 1
VAL_LEAK_NG_IDX = 2
VAL_FD_NG_IDX = 3
VAL_SKIP_IDX = 4

# ----------------------------------------------------------

def get_leak_bytes(line):
    split = line.split()
    len_split = len(split)

    leak_bytes = 0
    for i in range(len_split):
        for lost in (DEFINITELY, INDIRECTLY, POSSIBLY):
            if split[i] == lost and i + 2 < len_split and split[i + 2].isdigit():
                leak_bytes = int(split[i + 2])
                # print(f'lost:{lost}, leak:[{split[i + 2]}]')
                break

    return leak_bytes


def get_valgrind_leak_summary(stderr):
    sum_bytes = 0
    val_results = stderr.split('\n')

    checked = [0, 0, 0]

    for line in reversed(val_results):
        # print(f'reversed_line:{line}')
        if DEFINITELY in line:
            sum_bytes += get_leak_bytes(line)
            checked[0] = 1
        if INDIRECTLY in line:
            sum_bytes += get_leak_bytes(line)
            checked[1] = 1
        if POSSIBLY in line:
            sum_bytes += get_leak_bytes(line)
            checked[2] = 1

        if sum(checked) == 3:
            break

    # print valgrind result
    # print(f'\nvalgrind res:\n{stderr}')
    return sum_bytes


def get_open_fd(line):
    split = line.split()
    len_split = len(split)

    # print(f'line:{line}, split:{split}')
    fd = 0
    for i in range(len_split):
        if split[i] == FD_FLAG and split[i + 1].isdigit():
            fd = int(split[i + 1])
            # print(f'fd:{split[i + 1]}')
            break
    return fd


# FILE DESCRIPTORS: 3 open (3 std) at exit
def get_valgrind_fd_at_exit(stderr):

    val_results = stderr.split('\n')
    fd_at_exit = 0

    for line in reversed(val_results):
        if FD_FLAG in line:
            fd_at_exit = get_open_fd(line)
            break

    return fd_at_exit


def get_valgrind_res(stderr):
    leak_summary = get_valgrind_leak_summary(stderr)
    fd_at_exit = get_valgrind_fd_at_exit(stderr)
    return leak_summary, fd_at_exit


def run_cmd_with_valgrind(stdin=None, cmd=None):
    valgrind = VALGRIND + VALGRIND_OP
    try:
        res = subprocess.run(valgrind + cmd,
                             input=stdin,
                             capture_output=True,
                             text=True,
                             shell=True,
                             timeout=2)
        return res
    except subprocess.TimeoutExpired as e:
        print(e.cmd)


def run_minishell_with_valgrind(stdin, cmd):
    res_minishell = run_cmd_with_valgrind(stdin, cmd)
    print(f'cmd:[{stdin}]', end='\n')
    if res_minishell is None or res_minishell.stderr is None:
        return None
    leak_bytes, fd_at_exit = get_valgrind_res(res_minishell.stderr)
    print(f' minishell leaks      : {leak_bytes} bytes')
    print(f'           fd at exit : {fd_at_exit} open (3 std)')
    return leak_bytes, fd_at_exit


def run_bash_with_valgrind(stdin, cmd):
    res_bash = run_cmd_with_valgrind(stdin, cmd)
    if res_bash is None or res_bash.stderr is None:
        return None
    leak_bytes, fd_at_exit = get_valgrind_res(res_bash.stderr)
    print(f' bash leaks           : {leak_bytes} bytes')
    return leak_bytes, fd_at_exit


def run_both_with_valgrind(stdin):
    print("===== leak and fd test =====")
    if shutil.which(VALGRIND) is None:
        return None, None

    leak_res_minishell = run_minishell_with_valgrind(stdin, PATH_MINISHELL_LEAK)
    # leak_res_bash = run_bash_with_valgrind(stdin, PATH_BASH_LEAK)
    # return leak_res_minishell, leak_res_bash
    return leak_res_minishell


def put_valgrind_result(val_res, m_res):
    if m_res is None:
        print("valgrind result is None")
        return
    
    test_num, _, _, _, _ = val_res
    if m_res is None:
        print_color_str(YELLOW, f'[{test_num}. valgrind not found]')
        val_res[VAL_SKIP_IDX] += 1

    is_leak, fd = m_res
    if not is_leak and fd == 3:
        print_color_str(GREEN, f'[{test_num}. OK]')
        val_res[VAL_OK_IDX] += 1
    if is_leak:
        print_color_str(RED, f'[{test_num}. LEAK KO]')
        val_res[VAL_LEAK_NG_IDX] += 1
    if fd != 3:
        print_color_str(RED, f'[{test_num}. FD KO]')
        val_res[VAL_FD_NG_IDX] += 1

    val_res[VAL_TEST_NO_IDX] += 1
    print()


def put_total_valgrind_result(val_res):
    test_num, ok, leak_ng, fd_ng, skip = val_res
    print("#########################################")
    print(" LEAK TOTAL RESULT : ", end="")
    print_color_str_no_lf(GREEN, "OK ")
    print(f'{ok}, ', end="")
    print_color_str_no_lf(RED, "LEAK_NG ")
    print(f'{leak_ng}, ', end="")
    print_color_str_no_lf(RED, "FD_NG ")
    print(f'{fd_ng}, ', end="")
    print_color_str_no_lf(YELLOW, "SKIP ")
    print(skip, end="")
    print(f' (test case: {test_num - 1})')
    print("#########################################\n")
    if ok == test_num - 1:
        return 0
    else:
        return 1


def valgrind_test(test_input_list):
    test_num = 1
    ok = 0
    leak_ng = 0
    fd_ng = 0
    skip = 0
    val_result = [test_num, ok, leak_ng, fd_ng, skip]

    ko_case = []
    prev_ok = 0

    for stdin in test_input_list:
        m_res = run_both_with_valgrind(stdin)
        put_valgrind_result(val_result, m_res)
        if prev_ok == val_result[VAL_OK_IDX]:
            ko_case.append(stdin)
        prev_ok = val_result[VAL_OK_IDX]

    return put_total_valgrind_result(val_result), ko_case
