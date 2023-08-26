# minishell
Re-implemented a simple shell.  
It partially behaves like GNU Bash version 4.4.0.  

![demo](images/demo.gif)

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

## Implement
- Display a prompt.
- Have a working history.
- Search and launch the right executable (baced on the PATH variable or using a relative or an absolute path).
- Handle `''` (single quote).
- Handle `""` (double quote).
- Redirections.
  - `<` : redirect input.
  - `>` : redirect output.
  - `<<` : here documents.
  - `>>` : redirect output in append mode.
- `|` : Pipes.
- Handle environment variables.
- Handle `$?`.
- Handle `ctrl+C`, `ctrl+D`, `ctrl+\`
- Builtins.
  - echo
  - cd
  - pwd
  - export
  - unset
  - env
  - exit
- `&&` : And.
- `||` : Or.
- `()` : Subshell.
- `*` : Wildcards.

More detail : [minishell's specification](https://github.com/habvi/42_minishell/wiki/minishell's-specification)

## Used external functions
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, malloc, free, write, access, open, read, close, fork, wait, waitpid, sigaction, exit, getcwd, chdir, stat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty
