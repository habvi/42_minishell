#ifndef MS_VAR_H
# define MS_VAR_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "ms_result.h"

/* declare */
# define DECLARE		"declare"
# define ATTR_NONE		""
# define ATTR_ENV		"-x"
# define ATTR_SHELL		"--"

/* var key */
# define KEY_PATH		"PATH"
# define KEY_PWD		"PWD"
# define KEY_OLDPWD		"OLDPWD"
# define KEY_HOME		"HOME"
# define KEY_CDPATH		"CDPATH"

# define ASSIGNMENT_STR	"="
# define ASSIGNMENT_CHR	'='

typedef struct s_context		t_context;
typedef struct s_var			t_var;
typedef struct s_hash_element	t_elem;
typedef struct s_hash_table		t_hash;

typedef enum e_var_attr
{
	VAR_NONE = 0,
	VAR_ENV = 1 << 0,
	VAR_SHELL = 1 << 1,
}	t_var_attr;

typedef struct s_variable
{
	char		*value;
	t_var_attr	attr;
}	t_var_info;

struct s_var
{
	t_hash	*hash;
	int		(*is_key_exist)(t_var *var, const char *key);
	char	*(*get_value)(t_var *var, const char *key);
	void	(*add)(t_var *var, \
					const char *key, \
					const char *value, \
					t_var_attr attr);
	void	(*join)(t_var *var, \
					const char *key, \
					const char *value, \
					t_var_attr attr);
	void	(*unset)(t_var *var, const char *key);
	void	(*print_detail)(t_var *var, t_var_attr attr, bool is_display_attr);
	void	(*clear)(t_var *var);
	void	(*env_print)(t_var *var);
	char	**(*convert_to_envp)(t_var *var);
};

/* init */
t_var		*set_default_environ(void);
void		set_default_pwd(t_var *var);
void		set_default_old_pwd(t_var *var);

/* create, dup */
void		var_declare_all(const char *const *args, \
							t_var *var, \
							uint8_t *status, \
							t_var_attr attr);
t_result	var_declare_arg(const char *const arg, t_var *var, t_var_attr attr);
t_var_info	*var_create_var_info_by_value_attr(const char *value, \
												t_var_attr attr);
char		*dup_var_key(const char *const arg, size_t *len);
char		*dup_var_value(const char *const arg);

/* add, join */
void		var_add(t_var *var, \
					const char *key, \
					const char *value, \
					t_var_attr attr);
void		var_join(t_var *var, \
						const char *key, \
						const char *value, \
						t_var_attr attr);

/* get */
char		*var_get_value(t_var *var, const char *key);
t_var_attr	var_get_attribute(t_var *var, const char *key);
int			var_is_key_exist(t_var *var, const char *key);

/* print */
void		var_print_detail(t_var *var, t_var_attr attr, bool is_display_attr);
void		var_sort_elems_by_key(t_elem **elems);

/* del */
void		var_unset(t_var *var, const char *key);
void		del_var_info(void **var_info);
void		var_clear(t_var *var);

/* environ */
void		env_print(t_var *var);
char		**var_convert_to_envp(t_var *var);

#endif //MS_VAR_H
