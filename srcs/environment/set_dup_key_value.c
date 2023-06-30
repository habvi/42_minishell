#include "minishell.h"
#include "ft_string.h"
#include "ft_mem.h"

bool	is_key_pwd_oldpwd(const char *key)
{
	return (ft_streq(key, KEY_PWD) || ft_streq(key, KEY_OLDPWD));
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
