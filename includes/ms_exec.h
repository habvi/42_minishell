#ifndef MS_EXEC_H
# define MS_EXEC_H

# include <stdbool.h>
# include <unistd.h>

# define CHILD_PID		0
# define READ			0
# define WRITE			1

# define EXIT_CODE_NO_SUCH_FILE		127

# define ERROR_MSG_NO_SUCH_FILE		"No such file or directory"
# define ERROR_MSG_CMD_NOT_FOUND	"command not found"

typedef struct s_deque_node	t_deque_node;
typedef struct s_deque		t_deque;
typedef struct s_params		t_params;

typedef struct s_command {
	t_deque			*head_command;
	char			**exec_command;
	t_deque_node	*next_command;
}	t_command;

typedef struct s_fd {
	int	pipefd[2];
	int	prev_fd;
}	t_fd;

/* call_builtin_command */
int				call_builtin_command(char *const *command, t_params *params);

/* check_command */
bool			is_first_command(int prev_fd);
bool			is_last_command(t_deque_node *next_cmd);

/* child_process */
int				handle_child_pipes(t_command *cmd, t_fd *fd);
void			child_process(t_command *cmd, \
								t_fd *fd, \
								char **environ, \
								t_params *params);

/* count_commands */
size_t			count_commands(char *const *commands);

/* exec */
int				execute_command(t_deque *dq_cmd, t_params *params);
t_deque_node	*get_next_command(t_deque_node *cmd, size_t *cmd_size);
char			**convert_command_to_array(t_deque_node *cmd, \
											const size_t size);

/* init */
void			init_cmd(t_command *cmd, t_deque *dq_cmd);
void			init_fd(t_fd *fd);

/* parent */
int				handle_parent_pipes(t_command *cmd, t_fd *fd);
int				parent_process(t_command *cmd, \
								t_fd *fd, \
								pid_t pid, \
								int *last_exit_status);

#endif //MS_EXEC_H
