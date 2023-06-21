#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

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

	int		(*set)(t_env *env, const char *key, const char *value);		// export key=value
	int		(*append)(t_env *env, char *key, char *value);	// export key+=value
	char	*(*get_value)(t_env *env, char *key);			//
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
char	*env_get_value(t_env *env, char *key);
void	env_print(t_env *env);
void	env_print_detail(t_env *env);
int		env_set(t_env *env, const char *key, const char *value);
int		env_append(t_env *env, char *key, char *value);
void	env_unset(t_env *env, const char *key);

#endif //MINISHELL_H
