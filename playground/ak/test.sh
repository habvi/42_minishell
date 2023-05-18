#!/bin/bash
assert() {
  input="$1"

  expected=`echo $(($input))`
#   echo "expected:[$expected]"
  actual=`./a.out "$input"`

  if [ "$actual" = "$expected" ]; then
    echo -e "\033[32m[OK] input : $input \\n => actual   = $actual\033[00m\\n"
  else
    echo -e "\033[31m[NG] input : $input \\n => actual   = $actual\\n    expected = $expected\033[00m\\n"
  fi
}

make re

assert 0
assert 42
assert "1 + 2"
assert "1 + 2 - 1"
assert "(1 + 2) * 2"
assert "(42 / 2 - 1) / 2"

echo END
