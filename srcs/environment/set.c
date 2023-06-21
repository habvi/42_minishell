#include "minishell.h"
#include "ft_hash.h"

// key expected `name` -> void ...?
int	env_set(t_env *env, char *key, char *value)
{
	// strdup key, value
	// set to hash
	if (hs_set_key(env->hash, key, value) == HASH_ERROR)
		return (FAILURE); // todo: hs_clear();
	return (SUCCESS);
}

// key expected `name` -> void ...?
int	env_append(t_env *env, char *key, char *value)
{
	// strdup key, value
	// set to hash
	if (hs_set_key(env->hash, key, value) == HASH_ERROR)
		return (FAILURE); // todo: hs_clear();
	return (SUCCESS);
}

