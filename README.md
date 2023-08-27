# minishell
Re-implemented a simple shell.  
It partially behaves like GNU Bash version 4.4.0.  

![demo](images/demo.gif)

<br>

## Usage (Linux / MacOS)

### Install GNU readline
```shell
make readline
```

### Compile
```shell
make
```

### Execute minishell
```shell
./minishell
```

<br>

## Basic Minishell Features
- Shell Syntax
  - Single Quotes : `'`
  - Double Quotes : `"`

- Shell Commands
  - Simple Commands
  - Pipelines : `|`
  - Lists of Commands : `&&`, `||`
  - Grouping Commands : `(`, `)`

- Shell Parameters
  - Special Parameters : `$?`

- Shell Expansions
  - Shell Parameter Expansion
  - Word Splitting
  - Pattern Matching : `*`
  - Quote Removal

- Redirections
  - Redirecting Input : `<`
  - Redirecting Output : `>`
  - Appending Redirected Output : `>>`
  - Here Documents : `<<`

- Executing Commands
  - Simple Command Expansion
  - Command Search and Execution
  - Environment
  - Exit Status
  - Signals : SIGINT(`^C`), SIGQUIT(`^\`)

- Shell Builtin Commands
  - cd
  - echo
  - env
  - exit
  - export
  - pwd
  - unset

- Shell Variables
  - CDPATH
  - HOME
  - OLDPWD
  - PATH
  - PWD
  - SHLVL

- Command Line Editing : EOF(`^D`)

- History

More detail : [minishell's specification](https://github.com/habvi/42_minishell/wiki/minishell's-specification)

<br>

## Used external functions
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, malloc, free, write, access, open, read, close, fork, wait, waitpid, sigaction, exit, getcwd, chdir, stat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty

<br>

## Author
- [ak0327](https://github.com/ak0327)
- [habvi](https://github.com/habvi)