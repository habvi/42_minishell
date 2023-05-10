#!/usr/bin/env bats

dir="../../"

#leak=""
leak="SANI"
#leak="VAL"

setup() {
    load ./bats-assert/load
    load ./bats-support/load
}

setup_file() {
    if [ "$leak"="SANI" ]; then
        make sani -C $dir
    else
        make re -C $dir
    fi
}

@test "0 arg" {
    run $dir./a.out
    assert_equal "$status" 1
    assert_equal "$output" ""
}

@test "1 arg-1" {
    run $dir./a.out b
    assert_equal "$status" 0
    assert_equal "$output" "B"
    [[ "$output" != *"detected memory leaks"* ]]
}

@test "1 arg-2" {
    run $dir./a.out ""
    assert_equal "$status" 0
    assert_equal "$output" ""
    [[ "$output" != *"detected memory leaks"* ]]
}

@test "1 arg-3" {
    run $dir./a.out abc
    assert_equal "$status" 0
    assert_equal "$output" ABC
    [[ "$output" != *"detected memory leaks"* ]]
}

@test "2 arg" {
    run $dir./a.out a b
    assert_equal "$status" 1
    assert_equal "$output" ""
    [[ "$output" != *"detected memory leaks"* ]]
}

@test "3 arg" {
    run $dir./a.out a b c
    assert_equal "$status" 1
    assert_equal "$output" ""
    [[ "$output" != *"detected memory leaks"* ]]
}
