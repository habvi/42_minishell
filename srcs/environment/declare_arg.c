#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

// all malloc
// key=value -> key, = ,value, attr
t_var_info	*env_create_var_info(const char *value, t_var_attr attr)
{
	t_var_info	*info;

	info = (t_var_info *)x_malloc(sizeof(t_var_info));
	if (!info)
		ft_abort();
	info->value = ft_strdup_abort(value);
	info->attr = attr;
	return (info);
}

static void	set_key_info_pair(t_env *env, \
								const char *key, \
								const t_var_info *var_info, \
								const t_env_op op)
{
	if (op == ENV_ADD)
		env->add(env, key, var_info);
	else if (op == ENV_JOIN)
		env->join(env, key, var_info);
}

static void	clear_key_value_info(char *key, char *value, t_var_info *var_info)
{
	ft_free(&key);
	ft_free(&value);
	del_var_info((void **)&var_info);
}

// arg: key=value
t_result	env_declare_arg(const char *const arg, t_env *env, t_var_attr attr)
{
	t_result	result;
	char		*key;
	char		*value;
	t_var_info	*var_info;
	t_env_op	op;

	result = separate_env_variables(arg, &key, &value, &op);
	if (result == FAILURE || result == CONTINUE)
		return (result);
	var_info = env_create_var_info(value, attr);
	set_key_info_pair(env, key, var_info, op);
	clear_key_value_info(key, value, var_info);
	return (result);
}
