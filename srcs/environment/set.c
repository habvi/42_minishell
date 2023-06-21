#include "minishell.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_string.h"

// strdup key, value
int	env_set(t_env *env, const char *key, const char *value)
{
	char	*dup_key;
	char	*dup_value;

	dup_key = ft_strdup(key);
	if (!dup_key)
		return (FAILURE);
	dup_value = ft_strdup(value);
	if (!dup_value)
	{
		ft_free(dup_key);
		return (FAILURE);
	}
	if (hs_set_key(env->hash, dup_key, dup_value) == HASH_ERROR)
	{
		ft_free(dup_key);
		ft_free(dup_value);
		return (FAILURE);
	}
	return (SUCCESS);
}

// key expected `name` -> void ...?
int	env_append(t_env *env, char *key, char *value)
{
	// strdup key, value
	// set to hash
	if (hs_set_key(env->hash, key, value) == HASH_ERROR)
		return (FAILURE);
	return (SUCCESS);
}
