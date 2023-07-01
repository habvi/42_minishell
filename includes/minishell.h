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
# define UNREACHABLE	(-1)

/* size */
# define ENV_LIST_SIZE	256

/* SIGNAL */
# define STATUS_SIG_BASE	128

/* string */
# define SHELL_NAME		"minishell"
# define PROMPT_NAME	"minishell "

/* pwd */
# define KEY_PWD		"PWD"
# define KEY_OLDPWD		"OLDPWD"

/* declare */
# define DECLARE		"declare"
# define ATTR_NONE		""
# define ATTR_ENV		"-x"
# define ATTR_SHELL		"--"

# define SHELL_INIT				"shell-init"
# define ERROR_MSG_GETCWD		"getcwd: cannot access parent directories"
# define ERROR_MSG_RETRIEVE_CWD	"error retrieving current directory"

typedef enum e_result			t_result;
typedef struct s_hash_element	t_elem;
typedef struct s_env			t_env;
typedef struct s_hash_table		t_hash;

typedef enum e_result
{
	PROCESS_ERROR = -1,
	SUCCESS = 0,
	FAILURE = 1,
	CONTINUE = 2,
}	t_result;

typedef enum e_var_attr
{
	VAR_NONE = 0b00,
	VAR_ENV = 0b01,
	VAR_SHELL = 0b10,
	VAR_ALL = 0b11,
}	t_var_attr;

typedef enum e_env_op
{
	ENV_ADD,
	ENV_JOIN,
}	t_env_op;

typedef struct s_variable
{
	char		*value;
	t_var_attr	attr;
}	t_var_info;

typedef struct s_context
{
	t_env	*env;
	bool	is_interactive;
	char	*internal_pwd;
	uint8_t	status;
}	t_context;

// key - var_info paris
struct s_env
{
	t_hash	*hash;
	int		(*is_key_exist)(t_env *env, const char *key);
	char	*(*get_value)(t_env *env, char *key);
	void	(*add)(t_env *env, const char *key, const t_var_info *info);
	void	(*join)(t_env *env, const char *key, const t_var_info *var_info);
	void	(*unset)(t_env *env, const char *key);
	void	(*print)(t_env *env);
	void	(*print_detail)(t_env *env, t_var_attr attr);
	void	(*clear)(t_env *env);
};

// temporarily here ...
/* debug */
void		debug_func(const char *func_name, const int line_num);
void		debug_2d_array(char **array);

/* environment */
t_env		*set_default_environ(t_context *context);
void		set_default_old_pwd(t_env *env);
void		set_default_pwd(t_env *env);

t_var_info	*env_create_var_info(const char *value, t_var_attr attr);
t_result	env_declare_arg(const char *const arg, t_env *env, t_var_attr attr);
char		*dup_env_key(const char *const arg, size_t *len);
char		*dup_env_value(const char *const arg);
char		*ft_strdup_abort(const char *str); // todo
void		env_dup_key_info_pair(const char *key, \
								const t_var_info *info, \
								char **dup_key, \
								t_var_info **dup_info);
char		*env_get_value(t_env *env, char *key);
t_var_attr	env_get_attribute(t_env *env, char *key);
t_result	separate_env_variables(const char *const arg, \
									char **key, \
									char **value, \
									t_env_op *op);
int			env_is_key_exist(t_env *env, const char *key);

void		env_add(t_env *env, const char *key, const t_var_info *info);
void		env_create_info_add(t_env *env, \
								const char *key, \
								const char *value, \
								t_var_attr attr);
void		env_join(t_env *env, const char *key, const t_var_info *var_info);
void		env_create_info_join(t_env *env, \
									const char *key, \
									const char *value, \
									t_var_attr attr);

void		env_print(t_env *env);
void		env_print_detail(t_env *env, t_var_attr attr);
void		sort_elems_by_key(t_elem **elems);

void		env_unset(t_env *env, const char *key);
void		del_var_info(void **var_info);
void		env_clear(t_env *env);

/* destroy */
void		destroy(t_context context);

/* input */
char		*input_line(void);

/* utils */
size_t		count_argv(const char *const *argc);
void		ft_abort(void);
char		*get_working_directory(char *for_whom);
bool		is_valid_key(const char *word);
bool		test_opendir(const char *path, int *tmp_err);

/* init */
void		init_context(t_context *context);

/* repl */
t_result	read_eval_print_loop(t_context *context);

#endif //MINISHELL_H
