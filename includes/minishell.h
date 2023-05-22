#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# define EXECVE_ERROR	(-1)
# define FORK_ERROR		(-1)
# define WAIT_ERROR		(-1)
# define PROCESS_ERROR	(-1)

# define CHILD_PID		0
# define PROMPT_NAME    "minishell "

# define EXIT_CODE_NO_SUCH_FILE	127

# define EXIT_MSG_NO_SUCH_FILE  "No such file or directory"

// temporarily here ...
/* debug */
void	debug_func(const char *func_name, const int line_num);
void	debug_2d_array(char **array);

/* exec */
void	child_process(char **commands, char **environ);
int		execute_command(char **exec_command);
int		parent_process(int *last_exit_status);

/* input */
char	*input_line(void);

#endif
