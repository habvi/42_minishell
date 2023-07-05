#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "ms_result.h"

/* return value */
# define CHDIR_ERROR	(-1)
# define CLOSE_ERROR	(-1)
# define DUP_ERROR		(-1) // dup && dup2
# define EXECVE_ERROR	(-1)
# define FORK_ERROR		(-1)
# define OPEN_ERROR		(-1)
# define PIPE_ERROR		(-1)
# define READ_ERROR		(-1)
# define WAIT_ERROR		(-1)
# define UNREACHABLE	(-1)

/* status */
// tokenize and parse
# define SYNTAX_ERROR		2

/* size */
# define VAR_LIST_SIZE	256

/* SIGNAL */
# define STATUS_SIG_BASE	128

/* string */
# define SHELL_NAME		"minishell"
# define PROMPT_NAME	"minishell "

# define SHELL_INIT				"shell-init"
# define ERROR_MSG_GETCWD		"getcwd: cannot access parent directories"
# define ERROR_MSG_RETRIEVE_CWD	"error retrieving current directory"

typedef struct s_var		t_var;
typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;
typedef struct s_ast		t_ast;

typedef struct s_context
{
	t_var	*var;
	bool	is_interactive;
	char	*internal_pwd;
	uint8_t	status;
}	t_context;

// temporarily here ...
/* debug */
void		debug_func(const char *func_name, const int line_num);
void		debug_2d_array(char **array);
void		debug_token_dq(t_deque *deque, const char *str);
void		debug_token_dq_node(t_deque_node *node);
void		debug_print_ast_tree(t_ast *root, const char *str);

/* destroy */
void		destroy_context(t_context context);

/* input */
char		*input_line(void);

/* utils */
size_t		count_argv(const char *const *argc);
void		ft_abort(void);
char		*get_working_directory(char *for_whom);
bool		is_valid_key(const char *word);
bool		is_valid_path(const char *path, int *tmp_err);
char		*x_ft_strdup(const char *str);

/* init */
void		init_context(t_context *context);

/* repl */
t_result	read_eval_print_loop(t_context *context);

#endif //MINISHELL_H
