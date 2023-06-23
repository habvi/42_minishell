#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>

/* return value */
# define EXECVE_ERROR	(-1)
# define FORK_ERROR		(-1)
# define WAIT_ERROR		(-1)
# define PIPE_ERROR		(-1)
# define PROCESS_ERROR	(-1)
# define UNREACHABLE	(-1)

# define SUCCESS		0
# define FAILURE		1
# define CONTINUE		2

/* size */
# define ENV_LIST_SIZE	256

/* SIGNAL */
# define STATUS_SIG_BASE	128

/* string */
# define SHELL_NAME		"minishell"
# define PROMPT_NAME	"minishell "

typedef struct s_env		t_env;
typedef struct s_hash_table	t_hash;

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
	int		status;
}	t_params;

struct s_env
{
	t_hash	*hash;

	char	*(*get_value)(t_env *env, char *key);				//
	int		(*set)(t_env *env, char *key, char *value, t_env_op op); // export
	void	(*unset)(t_env *env, const char *key);				// unset key

	void	(*print)(t_env *env);			// env
	int		(*print_detail)(t_env *env);	// export
};

// temporarily here ...
/* debug */
void	debug_func(const char *func_name, const int line_num);
void	debug_2d_array(char **array);

/* input */
char	*input_line(void);

/* init */
void	init_params(t_params *params);

/* environment */
int		declare_arg(const char *const arg, t_env *env, int *status);
int		dup_env_key(const char *const arg, char **key, size_t *len);
int		dup_env_value(const char *const arg, char **value);
char	*env_get_value(t_env *env, char *key);
t_env	*init_environ(void);
int		env_print_detail(t_env *env);
void	env_print(t_env *env);
int		separate_env_variables(const char *const arg, \
								char **key, \
								char **value, \
								t_env_op *op);
int		env_set(t_env *env, char *key, char *value, t_env_op op);
void	env_unset(t_env *env, const char *key);

/* utils */
// size_t	count_commands(char *const *commands);
size_t	count_argv(const char *const *argc);
void	ft_abort(void);
bool	is_valid_key(const char *word);

#endif //MINISHELL_H
