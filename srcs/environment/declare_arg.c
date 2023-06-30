#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"

t_result	env_declare_arg(const char *const arg, t_context *context)
{
	t_result	result;
	char		*key;
	char		*value;
	t_env_op	op;

	result = env_separate_key_value(arg, &key, &value, &op);
	if (result == FAILURE || result == CONTINUE)
		return (result);
	if (is_key_pwd_oldpwd(key)) // todo: bool is_init ?
		env_set_pwd_dup_key_value(context, key, &value, op);
	else
		env_set_dup_key_value(context->env, key, value, op);
	ft_free(&key);
	ft_free(&value);
	return (result);
}

t_result	env_init_declare_arg(const char *const arg, t_context *context)
{
	t_result	result;
	char		*key;
	char		*value;
	t_env_op	op;

	result = env_separate_key_value(arg, &key, &value, &op);
	if (result == FAILURE || result == CONTINUE)
		return (result);
	env_set_dup_key_value(context->env, key, value, op);
	ft_free(&key);
	ft_free(&value);
	return (result);
}
