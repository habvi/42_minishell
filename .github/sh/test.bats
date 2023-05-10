#!/usr/bin/env bats

setup() {
    dir="../../"
    make re -C $dir
}

@test "test1" {
    result="$( $dir./a.out test )"
    expected="TEST"

    [ "$result" == "$expected" ]
    [ $? -eq 0 ]
}

@test "test2" {
    result="$( $dir./a.out 42Tokyo )"
    expected="42TOKYO"

    [ "$result" == "$expected" ]
    [ $? -eq 0 ]
}

@test "test3" {
    result="$( $dir./a.out abc )"
    expected="ABC"

    [ "$result" == "$expected" ]
    [ $? -eq 0 ]
}

@test "test4" {
    result="$( $dir./a.out 123 )"
    expected="123"

    [ "$result" == "$expected" ]
    [ $? -eq 0 ]
}

@test "test5" {
    result="$( $dir./a.out 123 qwe)"
    expected="123 QWE"

    [ "$result" == "$expected" ]
    [ $? -eq 0 ]
}

@test "test6" {
    result="$( $dir./a.out "")"
    expected=""

    [ "$result" == "$expected" ]
    [ $? -eq 0 ]
}

@test "test7" {
    result="$( $dir./a.out )"
    [ -z "$result" ]
    [ $? -eq 1 ]
}
