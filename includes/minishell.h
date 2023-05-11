#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# define EXECVE_ERROR	-1
# define FORK_ERROR		-1
# define WAIT_ERROR		-1
# define PROCESS_ERROR	-1

# define CHILD_PID		0

// exec
int		exec(char **commands);

// input
char    *input_line();

#endif
