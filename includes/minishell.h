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

/* exec */
int		exec(char **commands);

/* input */
char	*input_line(void);

#endif
