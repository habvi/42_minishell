#ifndef MS_VAR_H
# define MS_VAR_H

# include <stddef.h>

/* declare */
# define DECLARE		"declare"
# define ATTR_NONE		""
# define ATTR_ENV		"-x"
# define ATTR_SHELL		"--"

/* var key */
# define KEY_PWD		"PWD"
# define KEY_OLDPWD		"OLDPWD"

typedef enum e_env_op			t_env_op;
typedef enum e_result			t_result;

typedef struct s_context		t_context;
typedef struct s_var			t_var;
typedef struct s_hash_element	t_elem;
typedef struct s_hash_table		t_hash;

typedef enum e_var_attr
{
	VAR_NONE = 0b00,
	VAR_ENV = 0b01,
	VAR_SHELL = 0b10,
	VAR_ALL = 0b11,
}	t_var_attr;

typedef struct s_variable
{
	char		*value;
	t_var_attr	attr;
}	t_var_info;

// key - var_info paris
struct s_var
{
	t_hash	*hash;
	int		(*is_key_exist)(t_var *var, const char *key);
	char	*(*get_value)(t_var *var, char *key);
	void	(*add)(t_var *var, const char *key, const t_var_info *info);
	void	(*join)(t_var *var, const char *key, const t_var_info *var_info);
	void	(*unset)(t_var *var, const char *key);
	void	(*print)(t_var *var);
	void	(*print_detail)(t_var *var, t_var_attr attr);
	void	(*clear)(t_var *var);
};

/* init */
t_var		*set_default_environ(t_context *context);
void		set_default_old_pwd(t_var *var);
void		set_default_pwd(t_var *var);

/* create */
t_var_info	*env_create_var_info(const char *value, t_var_attr attr);
t_result	env_declare_arg(const char *const arg, t_var *var, t_var_attr attr);
char		*dup_env_key(const char *const arg, size_t *len);
char		*dup_env_value(const char *const arg);
char		*ft_strdup_abort(const char *str); // todo
void		env_dup_key_info_pair(const char *key, \
								const t_var_info *info, \
								char **dup_key, \
								t_var_info **dup_info);
void		env_add(t_var *var, const char *key, const t_var_info *info);
void		env_create_info_add(t_var *var, \
								const char *key, \
								const char *value, \
								t_var_attr attr);
void		env_join(t_var *var, const char *key, const t_var_info *var_info);
void		env_create_info_join(t_var *var, \
									const char *key, \
									const char *value, \
									t_var_attr attr);

/* get */
char		*env_get_value(t_var *var, char *key);
t_var_attr	env_get_attribute(t_var *var, char *key);
t_result	separate_env_variables(const char *const arg, \
									char **key, \
									char **value, \
									t_env_op *op);
int			env_is_key_exist(t_var *var, const char *key);

/* print */
void		env_print(t_var *var);
void		env_print_detail(t_var *var, t_var_attr attr);
void		sort_elems_by_key(t_elem **elems);

/* del */
void		env_unset(t_var *var, const char *key);
void		del_var_info(void **var_info);
void		env_clear(t_var *var);

#endif //MS_VAR_H
