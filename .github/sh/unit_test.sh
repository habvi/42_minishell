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
        make
    else
        make >/dev/null 2>&1
    fi

    if [ $? -eq $MAKE_FAILURE ]; then
        return $EXIT_FAILURE
    fi
    return $EXIT_SUCCESS
}

exec_test() {
    if [ $1 -eq $EXIT_FAILURE ]; then
        return $EXIT_FAILURE
    fi

    if "${TEST_OUTPUT}"; then
        ./$PROGRAM_NAME
    else
        ./$PROGRAM_NAME >/dev/null 2>&1
    fi

    return $?
}

count_result() {
    if [ $1 -eq $EXIT_SUCCESS ]; then
        ((ok_cnt++))
    else
        ((ng_cnt++))
    fi
}

put_result() {
    if [ $1 -eq $EXIT_SUCCESS ]; then
        echo -e "${GREEN}$2OK${RESET}"
    else
        echo -e "${RED}$2NG${RESET}"
    fi
}

put_total_result() {
    echo "Total tests : $total_cnt"
    echo -e " ${GREEN}OK         : $ok_cnt${RESET}"
    echo -e " ${RED}NG         : $ng_cnt${RESET}"
    echo -e " ${YELLOW}SKIP       : $pass_cnt${RESET}"
}

# init
total_cnt=0
ok_cnt=0
ng_cnt=0
pass_cnt=0
status=0

cd $TEST_DIR

for dir in *; do
    status=$EXIT_SUCCESS
    ((total_cnt++))
    echo -e "[TEST $total_cnt] $dir"
#     echo -e "path:$PWD"
    if [ -d "$dir" ]; then
        cd $dir
        if [ -f Makefile ]; then
            exec_make $dir
            status=$?
            put_result $status " Make : "

            if [ $status -ne $EXIT_SUCCESS ]; then
                break
            fi

            exec_test $status
            status=$?
            put_result $status  " Test : "

        else
            echo -e " ${YELLOW}SKIP${RESET}"
        fi

        count_result $status
        echo ""
        cd ..
    else
        ((pass_cnt++))
    fi

done


put_total_result

if [ $ng_cnt -gt 0 ]; then
    exit $EXIT_FAILURE
fi
exit $EXIT_SUCCESS