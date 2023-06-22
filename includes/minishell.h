#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>

# define EXECVE_ERROR	(-1)
# define FORK_ERROR		(-1)
# define WAIT_ERROR		(-1)
# define PIPE_ERROR		(-1)
# define PROCESS_ERROR	(-1)
# define FATAL_ERROR	(-1)
# define UNREACHABLE	FATAL_ERROR

# define SUCCESS		0
# define FAILURE		1

# define ENV_LIST_SIZE	256

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
	int 	(*set)(t_env *env, char *key, char *value, t_env_op op); // export
	void	(*unset)(t_env *env, const char *key);				// unset key

	void	(*print)(t_env *env);			// env
	void	(*print_detail)(t_env *env);	// export
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
t_env	*init_environ(void);
char	*env_get_value(t_env *env, char *key);
void	env_print(t_env *env);
void	env_print_detail(t_env *env);
int 	env_set(t_env *env, char *key, char *value, t_env_op op);
void	env_unset(t_env *env, const char *key);

/* utils */
// size_t	count_commands(char *const *commands);
size_t	count_argv(char *const *argc);
bool	is_valid_key(const char *word);

#endif //MINISHELL_H
