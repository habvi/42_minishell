#!/bin/bash

# setting
TEST_DIR="test"
PROGRAM_NAME=a.out
MAKE_OUTPUT=false
TEST_OUTPUT=false

# const
EXIT_SUCCESS=0
EXIT_FAILURE=1
MAKE_FAILURE=2
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RESET='\033[0m'

# func
exec_make() {
    if "${MAKE_OUTPUT}"; then
        make -C $1
    else
        make -C $1 >/dev/null 2>&1
    fi

    if [ $? -eq $MAKE_FAILURE ]; then
        make_res=$EXIT_FAILURE
    else
        make_res=$EXIT_SUCCESS
    fi

    put_result $make_res " Make : "
    return $make_res
}

exec_test() {
    if [ $1 -eq $EXIT_FAILURE ]; then
        return $EXIT_FAILURE
    fi

    if "${TEST_OUTPUT}"; then
        ./$2/$PROGRAM_NAME
    else
        ./$2/$PROGRAM_NAME >/dev/null 2>&1
    fi

    test_res=$?
    put_result $test_res  " Test : "
    return $test_res
}

count_result() {
    if [ $1 -eq $EXIT_SUCCESS ]; then
        ((ok_cnt++))
    fi
}

put_result() {
    if [ $1 -eq $EXIT_SUCCESS ]; then
        echo -e "$2${GREEN}OK${RESET}"
    else
        echo -e "$2${RED}NG${RESET}"
    fi
}

put_total_result() {
    echo " ------------------------------------"
    echo " *           TOTAL RESULT           *"
    echo " ------------------------------------"
    echo -e "  ${GREEN}OK : $ok_cnt / $total_cnt${RESET}"

    ng_cnt=$(($total_cnt - $ok_cnt))
    if [ $ng_cnt -ne 0 ]; then
        echo -e "  ${RED}NG : $ng_cnt / $total_cnt${RESET}"
    fi
    echo ""
}

is_dir_exist() {
    if [ -d $1 ]; then
        return 0
    fi
    return 1
}

is_makefile_exist() {
    if [ -f "$dir"/Makefile ]; then
        return 0
    fi
    return 1
}

if_make_success() {
    if [ $status -eq $EXIT_SUCCESS ]; then
        return 0
    fi
    return 1
}

# init
total_cnt=0
ok_cnt=0
status=0

cd $TEST_DIR

echo " ------------------------------------"
echo " *            TEST START            *"
echo " ------------------------------------"

for dir in *; do
    if ! is_dir_exist $dir; then
        continue
    fi

    if ! is_makefile_exist $dir; then
        continue
    fi
    ((total_cnt++))
    echo -e "[TEST $total_cnt] $dir"
#     echo -e "path:$PWD"

    exec_make $dir
    exec_test $? $dir
    count_result $?
    echo ""

done


put_total_result

if [ $ng_cnt -gt 0 ]; then
    exit $EXIT_FAILURE
fi
exit $EXIT_SUCCESS