#include "minishell.h"
#include "ft_hash.h"
#include "ft_string.h"

// return value of key
// if key not found or value is NULL, returns empty string
// use case : expansion, etc.
char	*env_get_value(t_env *env, char *key)
{
	char	*value;
	char	*dup_value;

	value = hs_get_value(env->hash, key);
	if (!value)
		value = "";
	dup_value = ft_strdup(value);
	if (!dup_value)
		ft_abort();
	return (dup_value);
}
