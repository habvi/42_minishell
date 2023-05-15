#!/usr/bin/env bats

setup() {
# path based test.bats ?
    load bats-assert/load
    load bats-support/load

    # todo: set-up outfile, dir path
}

#######################################################################
##                             echo                                  ##
#######################################################################
@test "/bin/echo hello" {
  # BW02: Using flags on `run` requires at least BATS_VERSION=1.5.0.
#  bats_require_minimum_version 1.5.0

  echo "[TEST]" >&3
  echo "input file" >&3
  cat -e .github/sh/input1 >&3
  echo "" >&3
  echo "-----------------------" >&3

  # Run minishell and copy output array and status
  run ! --separate-stderr bash -c "<.github/sh/input1 ./minishell"

#  echo "original status, arrays" >&3
#  echo " status  : [$status]" >&3
#  echo " stdout(${#output[@]}): [${output[*]}]" >&3 # size=1, delim=\n
#  echo " stderr(${#stderr[@]}): [${stderr[*]}]" >&3
#  echo "-----------------------" >&3

  status_m=$status
  # delim by IFS
  IFS=$'\n'
  out_m=($output)

  err_arr=($stderr)
  err_m=()

  # minishell: error_message -> error_ms
  for elem in "${err_arr[@]}"; do
    if [[ ${elem} =~ minishell: ]];
    then
      echo $elem >&3
      err_m+=(${elem#minishell: })
    fi
  done

  echo "" >&3

  echo "====== minishell ======" >&3
  echo "status:$status_m" >&3
  echo "" >&3
  echo "out_m" >&3
  echo " out_m: [${out_m[*]}]" >&3
  echo " size :${#out_m[@]}" >&3
  echo "" >&3
  echo "err_m" >&3
  echo " err_m: [${err_m[*]}]" >&3
  echo " size :${#err_m[@]}" >&3
  echo -e "\n-----------------------" >&3

  run ! --separate-stderr bash -c "<.github/sh/input1 bash"
  status_b=$status
  out_b=($output)
  err_arr=($stderr)
  err_b=()

  # bash: error_message -> error_ms
  for elem in "${err_arr[@]}"; do
    if [[ ${elem} =~ bash: ]];
    then
#      echo "[$elem]->[${elem#bash: line *: }]" >&3
      err_b+=(${elem#bash: line *: })
    fi
  done

  echo "====== bash ======" >&3

  echo "status:$status_b" >&3
  echo "" >&3
  echo "out_b" >&3
  echo " out_b: [${out_b[*]}]" >&3
  echo " size :${#out_b[@]}" >&3
  echo "" >&3
  echo "err_b" >&3
  echo " err_b: [${err_b[*]}]" >&3
  echo " size :${#err_b[@]}" >&3
  echo -e "\n-----------------------" >&3

  # Run minishell and copy output array and status


#  run bash -c echo -n -e "$cmd | ./minishell"
  assert_equal "$status_m" "$status_b"
  assert_equal "$out_m" "$out_b"
  assert_equal "$err_m" "$err_b"
}

#######################################################################
##                              ls                                   ##
#######################################################################

@test "/bin/ls" {
    skip

    cmd="/bin/ls"
    status_bash=0
    status_minishell=0

    bash -c "$cmd"         > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_b)   2> >(sed 's/bash: line 1: //' >err_b) || status_bash=$?
    ./minishell <<< "$cmd" > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_m)   2> >(sed 's/minishell : //' >err_m)   || status_minishell=$?

    diff_result_stdout="$(diff out_m out_b | wc -l | tr -d ' ')"
    diff_result_stderr="$(diff err_m err_b | wc -l | tr -d ' ')"

    assert_equal "$diff_result_stdout" "0"
    assert_equal "$diff_result_stderr" "0"
    assert_equal "$status_minishell" "$status_bash"
}

@test "/bin/ls -l" {
    skip

    cmd="/bin/ls -l"
    status_bash=0
    status_minishell=0
    bash -c "$cmd"         > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_b)   2> >(sed 's/bash: line 1: //' >err_b) || status_bash=$?
    ./minishell <<< "$cmd" > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_m)   2> >(sed 's/minishell : //' >err_m)   || status_minishell=$?

    diff_result_stdout="$(diff out_m out_b | wc -l | tr -d ' ')"
    diff_result_stderr="$(diff err_m err_b | wc -l | tr -d ' ')"

    assert_equal "$diff_result_stdout" "0"
    assert_equal "$diff_result_stderr" "0"
    assert_equal "$status_minishell" "$status_bash"
}


#######################################################################
##                           error                                   ##
#######################################################################

@test "[exec failure] /bin/echooo hello" {
    skip

    cmd="/bin/echooo hello"
    status_bash=0
    status_minishell=0
    bash -c "$cmd"         > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_b)   2> >(sed 's/bash: line 1: //' >err_b)|| status_bash=$?
    ./minishell <<< "$cmd" > >(grep -v "out_b" | grep -v "out_m" | grep -v "err_b" | grep -v "err_m" >out_m)   2> >(sed 's/minishell: //' >err_m)   || status_minishell=$?

    diff_result_stdout="$(diff out_m out_b | wc -l | tr -d ' ')"
    diff_result_stderr="$(diff err_m err_b | wc -l | tr -d ' ')"

    assert_equal "$diff_result_stdout" "0"
    assert_equal "$diff_result_stderr" "0"
    assert_equal "$status_minishell" "$status_bash"
}
