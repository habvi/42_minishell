#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_mem.h"

// arg: key=value
// arg: key
t_result	var_declare_arg(const char *const arg, t_var *var, t_var_attr attr)
{
	t_result	result;
	char		*key;
	char		*value;
	t_env_op	op;

	result = separate_env_variables(arg, &key, &value, &op);
	if (result == FAILURE || result == CONTINUE)
		return (result);
	if (op == ENV_ADD)
		var->add(var, key, value, attr);
	else if (op == ENV_JOIN)
		var->join(var, key, value, attr);
	ft_free(&key);
	ft_free(&value);
	return (result);
}
