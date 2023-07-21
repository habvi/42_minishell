import subprocess
from color import print_color_str, print_color_str_no_lf, RED, GREEN, MAGENTA, CYAN, COLOR_DICT

# ----------------------------------------------------------
# OUT_FILE = "pipe_test_out.txt"
PATH_MINISHELL = ["./minishell", "-i", "-t"]
# PATH_MINISHELL = ["./minishell"]
BASH_INIT_FILE = 'bash_init_file'
PATH_BASH = ["/bin/bash", "--init-file", BASH_INIT_FILE, "-i"]
# PATH_BASH = ["/bin/bash"]

# ----------------------------------------------------------
MINISHELL_PROMPT_PREFIX = "minishell "
MINISHELL_ERROR_PREFIX = "minishell: "
BASH_PROMPT_PREFIX = "bash "
BASH_ERROR_PREFIX = "bash: "
GITHUB_ERROR_PREFIX = ["cannot set terminal", "no job"]
BASH_DROP_WORDS = ["usage:"]

# ----------------------------------------------------------
STDOUT_IDX = 0
STDERR_IDX = 1
STATUS_IDX = 2
IS_EXITED_IDX = 3

# output test res
TEST_NO_IDX = 0
OK_IDX = 1
KO_IDX = 2
SKIP_IDX = 3

# ----------------------------------------------------------
# remove prompt and error prefix

def remove_prompt_prefix(err_list, prompt_prefix):
    ret = []
    for err in err_list:
        if err.startswith(prompt_prefix):
            continue
        ret.append(err)
    return ret


def remove_error_prefix(err_list, error_prefix):
    ret = []
    for err in err_list:
        if err.startswith(error_prefix):
            err = err.removeprefix(error_prefix)
        ret.append(err)
    return ret


def remove_drop_words(err_list, drop_words):
    ret = []
    for err in err_list:
        drop = False
        for word in drop_words:
            if word in err:
                drop = True
        if not drop:
            ret.append(err)

    return ret


def remove_github_error(err_list, err_prefixes):
    ret = []
    for err in err_list:
        if any(err.startswith(prefix) for prefix in err_prefixes):
            continue
        ret.append(err)
    return ret


def get_eval_stderr(stderr, prompt_prefix, error_prefix):
    if stderr is None:
        return None

    errors = stderr.split('\n')
    # print(f'errors:[{errors}]')
    if len(errors) > 0 and len(errors[-1]) == 0:
        del errors[-1]

    err_list = remove_prompt_prefix(errors, prompt_prefix)
    err_list = remove_error_prefix(err_list, error_prefix)
    err_list = remove_drop_words(err_list, BASH_DROP_WORDS)
    err_list = remove_github_error(err_list, GITHUB_ERROR_PREFIX)

    return err_list

# ----------------------------------------------------------
# run

def run_cmd(stdin=None, path=None):
    try:
        proc = subprocess.Popen(path,
                                stdin=subprocess.PIPE,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                text=True)

        stdout, stderr = proc.communicate(stdin, timeout=2)
        if proc.poll() is None:
            is_exited = False
        else:
            is_exited = True
        output_result = [stdout, stderr, proc.returncode, is_exited]
        return output_result

    except subprocess.TimeoutExpired as e:
        print(e.cmd)
        return None


def get_cmd_string_for_output(stdin):
    print_cmd = stdin \
        .replace("\t", "\\t") \
        .replace("\n", "\\n") \
        .replace("\v", "\\v") \
        .replace("\f", "\\f") \
        .replace("\r", "\\r")
    return print_cmd


def run_shell(stdin, cmd, prompt_pfx, err_pfx):
    output_result = run_cmd(stdin, cmd)
    if output_result:
        errors = get_eval_stderr(output_result[STDERR_IDX], prompt_pfx, err_pfx)
        output_result[STDERR_IDX] = errors
        return output_result
    return None


def run_both(stdin):
    res_minishell = run_shell(stdin,
                              PATH_MINISHELL,
                              MINISHELL_PROMPT_PREFIX,
                              MINISHELL_ERROR_PREFIX)
    res_bash = run_shell(stdin,
                         PATH_BASH,
                         BASH_PROMPT_PREFIX,
                         BASH_ERROR_PREFIX)

    return res_minishell, res_bash


# ----------------------------------------------------------

def put_title(stdin, test_no, status_only):
    print_cmd = get_cmd_string_for_output(stdin)
    print(f'{"-" * 50} TEST NO.{test_no} {"<STATUS ONLY>" if status_only else ""} {"-" * 50} ', end='\n')
    print(f' input cmd:[{print_cmd}]', end='\n')


def put_output(name, stdin, output_result):
    print(f'=== {name} ===')
    print(f' stdin  : [{stdin}]')
    print(f' stdout : [{COLOR_DICT[CYAN] + output_result[STDOUT_IDX] + COLOR_DICT["end"]}]')
    print(" stderr : [", end='')

    for err_out in output_result[STDERR_IDX]:
        print(COLOR_DICT[MAGENTA] + err_out + COLOR_DICT["end"])

    # for i in range(len(output_result[STDERR_IDX])):
    #     print(COLOR_DICT[MAGENTA] + output_result[STDERR_IDX][i] + COLOR_DICT["end"], end='')
    #     if i + 1 < len(output_result[STDERR_IDX]):
    #         print()
    print("]")
    print(f' status : {output_result[STATUS_IDX]}')
    print(f' exited : {output_result[IS_EXITED_IDX]}')
    print()


def put_result(stdin, val, m_res, b_res, status_only, ko_case):
    test_num, _, _ = val
    if m_res is None or b_res is None:
        print_color_str(RED, f'[{test_num}. timeout]')
        val[KO_IDX] += 1
    elif not status_only and m_res == b_res:
        print_color_str(GREEN, f'[{test_num}. OK]')
        val[OK_IDX] += 1
    elif status_only and m_res[STATUS_IDX] == b_res[STATUS_IDX]:
        print_color_str(GREEN, f'[{test_num}. OK]')
        val[OK_IDX] += 1
    else:
        print_color_str(RED, f'[{test_num}. KO]')
        ko_case.append([stdin, m_res, b_res])
        val[KO_IDX] += 1

    val[TEST_NO_IDX] += 1
    print()


# put
def put_output_and_result(test_no, stdin, val, m_res, b_res, status_only, ko_case):
    if m_res is None or b_res is None:
        print("test result is none")
        return

    put_title(stdin, test_no, status_only)

    put_output("minishell", stdin, m_res)
    put_output("bash", stdin, b_res)

    put_result(stdin, val, m_res, b_res, status_only, ko_case)


def put_total_result(val):
    test_num, ok, ko = val
    if ok == test_num - 1:
        color = GREEN
    else:
        color = RED
    print_color_str(color,
                    f"#########################################\n"
                    f"TOTAL RESULT (test case: {test_num - 1})\n"
                    f"  OK {ok}\n"
                    f"  KO {ko}\n"
                    f"#########################################\n\n")
    if ok == test_num - 1:
        return 0
    else:
        return 1


# ----------------------------------------------------------

def output_test(test_input_list, status_only):
    test_num = 1
    ok = 0
    ko = 0
    val = [test_num, ok, ko]
    ko_case = []
    test_no = 1

    for stdin in test_input_list:
        m_res, b_res = run_both(stdin)
        put_output_and_result(test_no, stdin, val, m_res, b_res, status_only, ko_case)
        test_no += 1

    return put_total_result(val), ko_case


# ----------------------------------------------------------
