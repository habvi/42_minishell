#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# include "ms_result.h"
# include "ft_dprintf.h"

/* return value */
# define ACCESS_ERROR	(-1)
# define CHDIR_ERROR	(-1)
# define CLOSE_ERROR	(-1)
# define CLOSEDIR_ERROR	(-1)
# define DUP_ERROR		(-1) // dup && dup2
# define EXECVE_ERROR	(-1)
# define FORK_ERROR		(-1)
# define OPEN_ERROR		(-1)
# define PIPE_ERROR		(-1)
# define READ_ERROR		(-1)
# define SIGACT_ERROR	(-1)
# define SIGEMPTY_ERROR	(-1)
# define STAT_ERROR		(-1)
# define UNLINK_ERROR	(-1)
# define UNREACHABLE	(-1)
# define WAIT_ERROR		(-1)

# define STR_PATH_DELIMITER		":"
# define CHR_PATH_DELIMITER		':'
# define STR_CURRENT_PATH		"./"
# define STR_SLASH				"/"
# define CHR_SLASH				'/'
# define CHR_NULL				'\0'
# define EMPTY_STR				"\0"
# define SPACE					' '
# define EMPTY_LINE				""
# define PATH_ROOT				"/"

# define OP_FORCED_INTERACTIVE	'i'
# define OP_TEST				't'
# define INVALID_OPTION			2

/* status */
// tokenize and parse
# define SYNTAX_ERROR				2
# define ERROR_MSG_SYNTAX			"syntax error near unexpected token"
# define SYNTAX_DEFAULT_ARG			"newline"
# define ERROR_TYPE_WARNING			"warning"
# define ERROR_MSG_HEREDOC_EOF		"here-document delimited by end-of-file"
# define ERROR_MSG_PROCESS_ERROR	"fatal error occurred"
# define ERROR_MSG_ABORT			"abort"

/* size */
# define VAR_LIST_SIZE	256

/* SIGNAL */
# define STATUS_SIG_BASE	128

/* string */
# define SHELL_NAME		"minishell"
# define PROMPT_NAME	"minishell "
# define HEREDOC_PROMPT	"> "

# define SHELL_EXIT				"exit\n"
# define SHELL_INIT				"shell-init"
# define ERROR_MSG_GETCWD		"getcwd: cannot access parent directories"
# define ERROR_MSG_RETRIEVE_CWD	"error retrieving current directory"

/* parse, exec */
# define IN_FD_INIT			STDIN_FILENO
# define OUT_FD_INIT		STDOUT_FILENO

/* utils */
# define RANDOM_FILENAME	"/dev/urandom"
# define RANDOM_BUF_SIZE	100
/* gnl */
# define BUFFER_SIZE    	1024
# define LF             	'\n'

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
	bool	is_return;
	bool	is_rl_event_hook_off;
}	t_context;

/* debug */
void		debug_func(const char *func_name, const int line_num);
void		debug_2d_array(char **array);
void		debug_token_dq(t_deque *deque, const char *str);
void		debug_token_dq_node(t_deque_node *node);
void		debug_print_ast_tree(t_ast *root, const char *str);
char		*get_tree_symbol(bool is_rhs);
char		get_tree_space(bool is_rhs);
void		debug_print_dp_target_str(const char *target_path, \
										const size_t len_target);
void		debug_print_each_dp(const bool *dp, \
								const char *match_str, \
								const size_t len_t, \
								size_t i);

/* destroy */
void		destroy_context(t_context context);

/* input */
char		*input_line(void);

/* utils */
size_t		count_argv(const char *const *argc);
char		*extend_str(char *left, char *right);
void		ft_abort(void);
char		*get_current_path(int *tmp_err);
char		*get_working_directory(const char *for_whom, t_result *result);
bool		is_getcwd_failure(const int tmp_err);
bool		is_valid_key(const char *word);
bool		is_valid_head(const char c);
bool		is_valid_after_head(const char c);
bool		is_valid_path(const char *path, int *tmp_err, t_result *result);
bool		is_a_directory(const char *path, t_result *result);
bool		is_a_directory_by_stat(const char *path, t_result *result);
bool		is_file_by_stat(const char *path, t_result *result);
bool		test_opendir_strict(const char *path, t_result *result);
char		*x_ft_itoa(int n);
char		**x_ft_split(char const *str, char c);
char		*x_ft_strdup(const char *str);
char		*x_ft_strndup(const char *str, const size_t maxlen);
char		*x_ft_strjoin(char const *s1, char const *s2);
char		*x_ft_substr(char const *str, const size_t start, size_t len);
char		*create_split_src_paths(t_var *var, const char *key);
char		*get_random_str(const size_t size);
/* gnl */
char		*ft_get_next_line(int fd, t_result *result);

/* init */
t_result	init_context(t_context *context, \
							bool is_forced_interactive, \
							bool is_rl_event_hook_off);
t_result	analyze_op(int argc, \
						char **argv, \
						bool *is_forced_interactive, \
						bool *is_rl_event_hook_off);
/* repl */
t_result	read_eval_print_loop(t_context *context);

/* path */
char		*get_next_path(char **path_list);
char		*create_executable_path(char *paths, \
									const char *const command, \
									t_result *result);
char		*create_accessible_path(char *paths, \
									const char *const command, \
									t_result *result);
char		*create_exec_path(const char *const *argv, \
								t_var *var, \
								size_t paths_len, \
								t_context *context);
char		*create_valid_path_by_judge(char *paths, \
								const char *const arg, \
								bool (*judge)(const char *path, t_result *res), \
								t_result *result);

/* error msg */
// arg, msg
void		puterr_cmd_msg(const char *const arg, const char *msg);
void		puterr_cmd_arg_msg(const char *cmd, \
								const char *const arg, \
								const char *msg);
void		puterr_cmd_quoted_arg_msg(const char *cmd, \
										const char *const arg, \
										const char *msg);
void		puterr_cmd_arg_msg_wo_colon(const char *cmd, \
										const char *const arg, \
										const char *msg);
void		puterr_msg_quoted_arg(const char *msg, const char *const arg);
void		puterr_whom_cmd_arg_msg(const char *for_whom, \
									const char *cmd, \
									const char *const arg, \
									const char *msg);
void		puterr_arg_op_msg(const char *const arg, const char op);
void		puterr_heredoc_wanted_eof(const char *delimiter);
void		puterr_env_option(const char *const arg);
void		puterr_env_argument(const char *const arg);
void		puterr_msg(const char *msg);

// set
void		puterr_cmd_msg_set_status(const char *const cmd, \
										const char *msg, \
										t_context *context, \
										uint8_t status);
void		put_path_err_set_status(const char *const cmd, \
									t_context *context, \
									size_t paths_len);
#endif //MINISHELL_H
