#!/bin/bash

# function
test() {
    input="$1"

    expected=`echo $(($input))`
#   echo "expected:[$expected]"
    actual=`./a.out "$input"`

    if [ "$actual" = "$expected" ]; then
        echo -e "\033[32m[OK] input : $input \\n  => actual   = $actual\033[00m\\n"
    else
        echo -e "\033[31m[NG] input : $input \\n  => expected = $expected\\n     actual   = $actual\033[00m\\n"
    fi
}

# prepare
echo COMPILE
make re

# test
echo "========================= TEST START ========================="
echo " ----- four arithmetic operations ----- "
test 0
test 42
test "1 + 2"
test "1 + 2 - 1"
test "( 1 + 2 ) * 2"
test "( 42 / 2 - 1 ) / 2"
test "( 1 + 2 * 3 ) + 2 + 3 * 9"
test "( 1 + 2 ) * ( 3 + 4 ) + 5"
test "( 1 + 2 * ( 3 + 4 ) ) * 5"
test "( ( 1 ) + ( 2 ) )"
test "( ( 1 ) + ( 2 ) * ( ( ( 3 ) ) ) )"
test "( ( 1 ) + ( 2 ) * ( ( ( ( 3 ) * ( 2 + ( 1 * 2 ) ) ) ) ) )"
test "( 1 + 2 + 3 + 4 + 5 ) * ( 42 - 42 + 1 ) / ( 1 + 1 ) * 5"
test "( 1 + 2 + 3 + 4 + 5 * ( 6 + 7 ) ) * ( 42 - 42 + 1 ) * ( 1 + 1 ) * 5"
test "( 1 + 2 + 3 + 4 + 5 * ( 6 + 7 ) * ( 8 - 9 + 1 ) ) * ( 42 - 42 + 1 ) * ( 1 + 1 ) * 5"
test "( 1 + 2 + 3 + 4 + 5 * ( 6 + 7 ) * ( 8 - 9 + 1 * ( 1 + 2 + 3 ) ) ) * ( 42 - 42 + 1 ) * ( 1 + 1 ) * 5"

echo " ----- priority like commands ----- "
# priority like pipeline commands
# `*` == `|`
# `+` == `&&`
# `-` == `||`

test "1 * 2 * 3 * 4 * 5   +   6 * 7"
test "1 * 2 * ( 3 + 4 )"
test "1   +   ( 2 * 3 + ( 4 + 5 ) * ( 7 * 8 + 9 ) )"
test "1 * 2 * 3 * 4 * 5   +   6 * 7   +   1 * 2 * ( 3 + 4 )   +   1   +   ( 2 * 3 + ( 4 + 5 ) * ( 7 * 8 + 9 ) )   +   5"


echo "=============================================================="

