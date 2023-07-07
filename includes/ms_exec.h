#ifndef MS_EXEC_H
# define MS_EXEC_H

# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include "ms_result.h"

# define CHILD_PID		0
# define READ			0
# define WRITE			1

# define EXIT_CODE_NO_SUCH_FILE		127

# define ERROR_MSG_NO_SUCH_FILE		"No such file or directory"
# define ERROR_MSG_CMD_NOT_FOUND	"command not found"

typedef struct s_ast		t_ast;
typedef struct s_context	t_context;
typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;

typedef struct s_fd {
	int	pipefd[2];
	int	prev_fd;
}	t_fd;

/* call_builtin_command */
uint8_t			call_builtin_command(const char *const *argv, \
										t_context *context);

/* check_command */
bool			is_first_command(int prev_fd);
bool			is_last_command(t_deque_node *next_cmd);

/* child_process */

/* exec */
t_result		execute_command(t_ast *ast, t_context *context);
t_deque_node	*get_next_command(t_deque_node *cmd, size_t *cmd_size);
char			**convert_command_to_array(t_deque_node *cmd, \
											const size_t size);

/* init */
void			init_fd(t_fd *fd);

/* is_single_builtin */
bool			is_command_builtin(const char *cmd);
bool			is_single_builtin(t_deque_node *cmd);

/* parent */

/* ast */
char		**convert_command_to_argv(t_deque *command);
t_result	handle_child_pipes(t_ast *self_node);
void		child_process(t_ast *self_node, \
							char **environ, \
							t_context *context);
t_result	handle_parent_pipes(t_ast *self_node);
t_result	parent_process(t_ast *self_node);

#endif //MS_EXEC_H
