#ifndef MS_EXEC_H
# define MS_EXEC_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include "ms_result.h"

# define CHILD_PID		0
# define IN				0
# define OUT			1
# define READ			0
# define WRITE			1
# define NO_OPTION		0

# define STATUS_PERMISSION			126
# define STATUS_NO_SUCH_FILE		127
# define STATUS_CMD_NOT_FOUND		127

# define ERROR_MSG_NO_SUCH_FILE		"No such file or directory"
# define ERROR_MSG_CMD_NOT_FOUND	"command not found"

typedef struct s_ast		t_ast;
typedef struct s_context	t_context;
typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;
typedef struct s_redirect	t_redirect;
typedef struct s_var		t_var;

typedef enum e_open_flag
{
	OPEN_FOR_IN = O_RDONLY,
	OPEN_FOR_OUT = O_CREAT | O_WRONLY | O_TRUNC,
	OPEN_FOR_APPEND = O_CREAT | O_WRONLY | O_APPEND
}	t_open_flag;

/* call_builtin_command */
uint8_t			call_builtin_command(const char *const *argv, \
										t_context *context);

/* check_command */
bool			is_first_command(int prev_fd);

/* child_process */

/* exec */
t_result		execute_command(t_ast *ast, t_context *context);
uint8_t			execute_external_command(char *const *argv, t_context *context);

/* is_single_builtin */
bool			is_command_builtin(const char *cmd);

/* parent */

/* ast */
char			**convert_command_to_argv(t_deque *command);
t_result		handle_child_pipes(t_ast *self_node);
void			child_process(t_ast *self_node, t_context *context);
t_result		handle_parent_pipes(t_ast *self_node);
t_result		parent_process(t_ast *self_node, t_context *context);
t_result		exec_command_each(t_ast *self_node, t_context *context);
void			execute_single_builtin(t_ast *self_node, t_context *context);
bool			is_single_builtin_command(t_ast *self_node);
bool			is_last_command_node(t_ast *self_node);
char			*get_head_token_str(t_deque *command);

t_result		get_last_command_status(pid_t pid, \
										int *wait_status, \
										uint8_t *last_status);
t_result		wait_all_child_process(int wait_status);
t_result		exec_handle_left_node(t_ast *self_node, t_context *context);
t_result		exec_handle_right_node(t_ast *self_node, t_context *context);

/* redirects */
t_result		redirect_fd(t_ast *self_node, t_context *context);
void			connect_redirect_to_proc(t_ast *self_node);
t_result		open_redirect_fd_and_save_to_proc(t_redirect *redirect, \
													int proc_fd[2]);

#endif //MS_EXEC_H
