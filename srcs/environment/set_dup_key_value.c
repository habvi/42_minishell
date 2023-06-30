#include "minishell.h"
#include "ft_string.h"
#include "ft_mem.h"

static char	*swap_pwd_value(char *value, const char *new_value)
{
	char	*dup_value;

	ft_free(&value);
	if (!new_value)
		return (NULL);
	dup_value = ft_strdup(new_value);
	if (!dup_value)
		ft_abort();
	return (dup_value);
}

// if (key == PWD/OLDPWD && value == NULL)
// -> get value from internal
static char	*update_pwd_by_internal(const char *key, \
									char *value, \
									t_context *context)
{
	t_env	*env;
	char	*new_value;

	env = context->env;
	if (ft_streq(key, KEY_PWD) && !value)
		new_value = swap_pwd_value(value, context->internal_pwd);
	else if (ft_streq(key, KEY_OLDPWD))
	{
		if (env->is_key_exist(env, KEY_OLDPWD) && !value) //todo: sep and move
			env->unset(env, KEY_OLDPWD);
		new_value = swap_pwd_value(value, context->internal_old_pwd);
	}
	else
		new_value = value;
	return (new_value);
}


// key : valid key
void	env_set_pwd_dup_key_value(t_context *context, \
									const char *key, \
									char **value, \
									t_env_op op)
{
	*value = update_pwd_by_internal(key, *value, context);
	env_set_dup_key_value(context->env, key, *value, op);
}

// key : valid key
void	env_set_dup_key_value(t_env *env, \
								const char *key, \
								const char *value, \
								t_env_op op)
{
	char	*dup_key;
	char	*dup_value;

	dup_key = ft_strdup(key);
	if (!dup_key)
		ft_abort();
	dup_value = NULL;
	if (value)
	{
		dup_value = ft_strdup(value);
		if (!dup_value)
			ft_abort();
	}
	env->set(env, dup_key, dup_value, op);
}
