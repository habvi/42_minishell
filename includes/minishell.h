#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

/* return value */
# define CLOSE_ERROR	(-1)
# define DUP_ERROR		(-1) // dup && dup2
# define EXECVE_ERROR	(-1)
# define FORK_ERROR		(-1)
# define OPEN_ERROR		(-1)
# define PIPE_ERROR		(-1)
# define READ_ERROR		(-1)
# define WAIT_ERROR		(-1)
// # define PROCESS_ERROR	(-1)
# define UNREACHABLE	(-1)

/* size */
# define ENV_LIST_SIZE	256

/* SIGNAL */
# define STATUS_SIG_BASE	128

/* string */
# define SHELL_NAME		"minishell"
# define PROMPT_NAME	"minishell "

/* pwd */
# define PWD			"PWD"
# define OLDPWD			"OLDPWD"

# define SHELL_INIT				"shell-init"
# define ERROR_MSG_GETCWD		"getcwd: cannot access parent directories"
# define ERROR_MSG_RETRIEVE_CWD	"error retrieving current directory"

typedef enum e_result		t_result;
typedef struct s_env		t_env;
typedef struct s_hash_table	t_hash;

// # define SUCCESS	0
// # define FAILURE	1
// # define CONTINUE	2

typedef enum e_result
{
	PROCESS_ERROR = -1,
	SUCCESS = 0,
	FAILURE = 1,
	CONTINUE = 2,
}	t_result;

typedef enum e_env_op
{
	ENV_ADD,
	ENV_JOIN,
}	t_env_op;

typedef struct s_params
{
	t_env	*env;
	bool	is_interactive;
	char	*pwd;
	char	*old_pwd;
	uint8_t	status;
}	t_params;

struct s_env
{
	t_hash	*hash;
	int		(*is_key_exist)(t_env *env, const char *key);
	char	*(*get_value)(t_env *env, char *key);
	void	(*set)(t_env *env, char *key, char *value, t_env_op op);
	void	(*unset)(t_env *env, const char *key);
	void	(*print)(t_env *env);
	void	(*print_detail)(t_env *env);
	void	(*clear)(t_env *env);
};

// temporarily here ...
/* debug */
void		debug_func(const char *func_name, const int line_num);
void		debug_2d_array(char **array);

/* environment */
void		env_clear(t_env *env);
t_result	declare_arg(const char *const arg, t_env *env);
char		*dup_env_key(const char *const arg, size_t *len);
char		*dup_env_value(const char *const arg);
char		*env_get_value(t_env *env, char *key);
t_env		*init_environ(void);
char		*init_old_pwd(t_env *env);
char		*init_pwd(t_env *env);
int			is_key_exist(t_env *env, const char *key);
void		env_print_detail(t_env *env);
void		env_print(t_env *env);
t_result	separate_env_variables(const char *const arg, \
								char **key, \
								char **value, \
								t_env_op *op);
void		env_set(t_env *env, char *key, char *value, t_env_op op);
void		env_unset(t_env *env, const char *key);

/* destroy */
void		destroy(t_params params);

/* input */
char		*input_line(void);

/* utils */
// size_t	count_commands(char *const *commands);
size_t		count_argv(const char *const *argc);
void		ft_abort(void);
char		*get_working_directory(char *for_whom);
bool		is_valid_key(const char *word);

/* init */
void		init_params(t_params *params);

/* repl */
t_result	read_eval_print_loop(t_params *params);

#endif //MINISHELL_H
