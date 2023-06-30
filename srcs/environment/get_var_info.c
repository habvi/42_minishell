#include "minishell.h"
#include "ft_hash.h"
#include "ft_string.h"

// return value of key
// if key not found or value is NULL, returns NULL.
// use case : expansion, etc.
char	*env_get_value(t_env *env, char *key)
{
	t_var_info	*var_info;
	char		*value;
	char		*dup_value;

	var_info = (t_var_info *)hs_get_value(env->hash, key);
	if (!var_info)
		return (NULL);
	value = var_info->value;
	if (!value)
		return (NULL);
	dup_value = ft_strdup(value);
	if (!dup_value)
		ft_abort();
	return (dup_value);
}

t_var_attr	env_get_attribute(t_env *env, char *key)
{
	t_var_info	*var_info;

	var_info = (t_var_info *)hs_get_value(env->hash, key);
	if (!var_info)
		return (VAR_NONE);
	return (var_info->attr);
}
