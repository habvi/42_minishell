#include "minishell.h"
#include "ft_hash.h"

int	env_set(t_env *env, char *key, char *value)
{
	t_deque_node	*target_node;

	target_node = hs_find_key(env->hash, key);
	if (target_node)
	{
		if (!value)
			return (SUCCESS);
		hs_update_value(&key, value, target_node, env->hash->del_value);
	}
	else
	{
		if (hs_add_to_table(env->hash, key, value) == HASH_ERROR)
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
