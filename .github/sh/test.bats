#!/usr/bin/env bats

setup() {
    dir="../../"
    make re -C $dir
}

@test "test1" {
    result="$( $dir./a.out test )"
    expected="TEST"
    [ "$result" == "$expected" ]
}

@test "test2" {
    result="$( $dir./a.out 42Tokyo )"
    expected="42TOKYO"
    [ "$result" == "$expected" ]
}

@test "test3" {
    result="$( $dir./a.out abc )"
    expected="ABC"
    [ "$result" == "$expected" ]
}

@test "test4" {
    result="$( $dir./a.out 123 )"
    expected="123"
    [ "$result" == "$expected" ]
}