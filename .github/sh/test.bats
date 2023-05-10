#!/usr/bin/env bats

dir="./../../"

setup() {
    load ./bats-assert/load
    load ./bats-support/load
}

setup_file() {
    make re -C $dir
}

@test "0 arg" {
    run $dir./a.out
    assert_equal "$status" 1
    assert_equal "$output" ""
    [[ "$output" != *"detected memory leaks"* ]]
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


@test "mkfile" {
    run echo hello
    run echo -e hello > out
    run cat out
    assert_equal "$output" "hello"
}
