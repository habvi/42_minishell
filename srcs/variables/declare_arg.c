#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_mem.h"
#include "ft_sys.h"

static void	set_key_info_pair(t_var *var, \
								const char *key, \
								const t_var_info *var_info, \
								const t_env_op op)
{
	if (op == ENV_ADD)
		var->add(var, key, var_info);
	else if (op == ENV_JOIN)
		var->env_join(var, key, var_info);
}

static void	clear_key_value_info(char *key, t_var_info *var_info)
{
	ft_free(&key);
	del_var_info((void **)&var_info);
}

// attr of declare is the arg_attr
// if arg_attr is NONE, use the attr of key ...(*)
//
// key    key_attr    arg_attr    declare_attr
// -------------------------------------------
// NULL    -           x           x
//                     -           -
//                     NONE        -  (*)
// !NULL   x           x           x
//                     -           -
//                     NONE        x  (*)
//         -           x           x
//                     -           -
//                     NONE        -  (*)
// todo: bit arithmetic ... ?
t_var_attr	get_declare_attr(t_var *var, \
								const char *key, \
								t_var_attr arg_attr)
{
	t_var_attr	declare_attr;

	if (arg_attr != VAR_NONE)
		return (arg_attr);
	declare_attr = var_get_attribute(var, key);
	if (declare_attr == VAR_NONE)
		declare_attr = VAR_SHELL;
	return (declare_attr);
}

// arg: key=value
// arg: key
t_result	var_declare_arg(const char *const arg, t_var *var, t_var_attr attr)
{
	t_result	result;
	char		*key;
	char		*value;
	t_var_info	*var_info;
	t_env_op	op;

	result = separate_env_variables(arg, &key, &value, &op);
	if (result == FAILURE || result == CONTINUE)
		return (result);
	var_info = var_create_var_info_for_set(var, key, value, attr);
	set_key_info_pair(var, key, var_info, op);
	clear_key_value_info(key, var_info);
	return (result);
}
