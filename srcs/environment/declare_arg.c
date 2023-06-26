#include "minishell.h"

t_result	declare_arg(const char *const arg, t_env *env)
{
	t_result	result;
	char		*key;
	char		*value;
	t_env_op	op;

	result = separate_env_variables(arg, &key, &value, &op);
	if (result == FAILURE || result == CONTINUE)
		return (result);
	env->set(env, key, value, op);
	return (result);
}
