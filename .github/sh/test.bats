#!/usr/bin/env bats

setup() {
# path based test.bats ?
    load bats-assert/load
    load bats-support/load
}

# path based makefile ?

#######################################################################
##                             echo                                  ##
#######################################################################
@test "/bin/echo hello" {
    run ./minishell <<< "/bin/echo hello"
    assert_equal "$output" "hello"
    assert_equal "$status" "0"
}

#######################################################################
##                              ls                                   ##
#######################################################################
# outfiles must be excluded in ls test

@test "/bin/ls" {
    cmd="/bin/ls"
    status_bash=0
    status_minishell=0

    bash -c "$cmd"         > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_b)   2> >(sed 's/bash: line 1: //' >err_b) || status_bash=$?
    ./minishell <<< "$cmd" > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_m)   2> >(sed 's/minishell : //' >err_m)   || status_minishell=$?

    diff_result_stdout="$(diff out_m out_b | wc -l | tr -d ' ')"
    diff_result_stderr="$(diff err_m err_b | wc -l | tr -d ' ')"

    assert_equal "$diff_result_stdout" "0"
    assert_equal "$diff_result_stderr" "0"
    assert_equal "$status_bash" "$status_minishell"
}

@test "/bin/ls -l" {
    cmd="/bin/ls -l"
    status_bash=0
    status_minishell=0
    bash -c "$cmd"         > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_b)   2> >(sed 's/bash: line 1: //' >err_b) || status_bash=$?
    ./minishell <<< "$cmd" > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_m)   2> >(sed 's/minishell : //' >err_m)   || status_minishell=$?

    diff_result_stdout="$(diff out_m out_b | wc -l | tr -d ' ')"
    diff_result_stderr="$(diff err_m err_b | wc -l | tr -d ' ')"

    assert_equal "$diff_result_stdout" "0"
    assert_equal "$diff_result_stderr" "0"
    assert_equal "$status_bash" "$status_minishell"
}


#######################################################################
##                           error                                   ##
#######################################################################

@test "[exec failure] /bin/echoo hello" {
    cmd="/bin/echooo hello"
    status_bash=0
    status_minishell=0
    bash -c "$cmd"         > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_b)   2> >(sed 's/bash: line 1: //' >err_b) || status_bash=$?
    ./minishell <<< "$cmd" > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_m)   2> >(sed 's/minishell: //' >err_m)   || status_minishell=$?

    diff_result_stdout="$(diff out_m out_b | wc -l | tr -d ' ')"
    diff_result_stderr="$(diff err_m err_b | wc -l | tr -d ' ')"

    assert_equal "$diff_result_stdout" "0"
    assert_equal "$diff_result_stderr" "0"
    assert_equal "$status_bash" "$status_minishell"
}