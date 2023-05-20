#!/bin/bash
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


echo COMPILE
make re
echo ========================= TEST START =========================
test 0
test 42
test "1 + 2"
test "1 + 2 - 1"
test "(1 + 2) * 2"
test "(42 / 2 - 1) / 2"

echo ==============================================================

