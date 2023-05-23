#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# define EXECVE_ERROR	(-1)
# define FORK_ERROR		(-1)
# define WAIT_ERROR		(-1)
# define PIPE_ERROR		(-1)
# define PROCESS_ERROR	(-1)

# define CHILD_PID		0
# define PROMPT_NAME    "minishell "
# define READ			0
# define WRITE			1

# define EXIT_CODE_NO_SUCH_FILE	127

# define EXIT_MSG_NO_SUCH_FILE  "No such file or directory"

typedef struct s_command {
	char	**head;
	char	**exec_command;
	char	**next_command;
}	t_command;

typedef struct s_fd {
	int	pipefd[2];
	int	prev_fd;
}	t_fd;

// temporarily here ...
/* debug */
void	debug_func(const char *func_name, const int line_num);
void	debug_2d_array(char **array);

/* exec */
bool	is_first_command(int prev_fd);
bool	is_last_command(char *next_cmd);
void	child_process(t_command *cmd, t_fd *fd, char **environ);
int		execute_command(t_command *commands);
int		handle_parent_pipes(t_command *cmd, t_fd *fd);
int		parent_process(\
					t_command *cmd, t_fd *fd, pid_t pid, int *last_exit_status);

/* input */
char	*input_line(void);

#endif
