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
# define FATAL_ERROR	(-1)

# define CHILD_PID		0
# define PROMPT_NAME    "minishell "
# define READ			0
# define WRITE			1

# define EXIT_CODE_NO_SUCH_FILE		127

# define ERROR_MSG_NO_SUCH_FILE		"No such file or directory"
# define ERROR_MSG_CMD_NOT_FOUND	"command not found"

typedef struct s_deque_node	t_deque_node;
typedef struct s_deque		t_deque;

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
void			debug_func(const char *func_name, const int line_num);
void			debug_2d_array(char **array);

/* exec */
// check_command.c
bool			is_first_command(int prev_fd);
bool			is_last_command(t_deque_node *next_cmd);
// child_pipes.c
int				handle_child_pipes(t_command *cmd, t_fd *fd);
// child_proces.c
void			child_process(t_command *cmd, t_fd *fd, char **environ);
// exec.c
int				execute_command(t_deque *command, bool *is_exit_shell);
t_deque_node	*get_next_command(t_deque_node *cmd, size_t *cmd_size);
char			**convert_command_to_array(t_deque_node *node, \
											const size_t size);

// init.c
void			init_cmd(t_command *cmd, t_deque *dq_cmd);
void			init_fd(t_fd *fd);
// parent_pipes.c
int				handle_parent_pipes(t_command *cmd, t_fd *fd);
// parenkt_process.c
int				parent_process(\
					t_command *cmd, t_fd *fd, pid_t pid, int *last_exit_status);

// exec_builtin_in_parent_proc
int				exec_builtin_in_parent_proc(t_command cmd, \
											t_deque_node *node, \
											bool *is_exit_shell);
size_t			pipe_cnt(t_deque_node *node);

/* input */
// input.c
char			*input_line(void);

#endif
