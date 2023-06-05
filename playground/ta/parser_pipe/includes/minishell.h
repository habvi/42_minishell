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

typedef struct s_deque_node				t_deque_node;
typedef struct s_deque					t_deque;
typedef struct s_abstract_syntax_tree	t_ast; //too long?

typedef struct s_command {
	t_deque			*head_command;
	char			**exec_command;
	t_deque_node	*next_command;
}	t_command;

typedef struct s_fd {
	int	pipefd[2];
	int	prev_fd;
}	t_fd;

// temporarily here ...
/* debug */
// put.c
void	debug_func(const char *func_name, const int line_num);
void	debug_2d_array(char **array);

/* exec */
// check_command.c
bool	is_first_command(int prev_fd);
bool	is_last_command(t_deque_node *next_cmd);
//bool	is_last_command(t_ast *next);
// child_pipes.c
int		handle_child_pipes(bool is_last_command, t_fd *fd);
// child_proces.c
void	child_process(t_ast *cmd, t_fd *fd, bool is_last_command);
// exec.c
int		execute_command(t_ast *ast);
// init.c
void	init_cmd(t_command *cmd, t_deque *dq_cmd);
void	init_fd(t_fd *fd);
// parent_pipes.c
int		handle_parent_pipes(bool is_last_command, t_fd *fd);
// parent_process.c
int		parent_process(bool is_last_command, \
						t_fd *fd, pid_t pid, int *last_status);
/* input */
// input.c
char	*input_line(void);

#endif
