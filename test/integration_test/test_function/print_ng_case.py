import glob


def print_ng_cases(test_res):
    if not test_res:
        return

    for file in glob.glob('ko_case_*_cmd.txt'):
        with open(file, 'r') as f:
            print(f.read())
    return
