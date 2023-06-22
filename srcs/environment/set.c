#include "minishell.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_string.h"

// todo: fatal error

// key=
static void	env_add(t_env *env, char *key, char *value, t_deque_node *target_node)
{
	if (!value)
		return ;
	hs_update_value(&key, value, target_node, env->hash->del_value);
}

static int	join_new_value(char *pre, char *new, char **joined)
{
	*joined = ft_strjoin(pre, new);
	if (!*joined)
		return (FAILURE);
	return (SUCCESS);
}

// key expected `name` -> void ...?
// key+=
static int	env_join(t_env *env, char *key, char *new_value, t_deque_node *target_node)
{
	t_elem	*elem;
	char	*joined_value;

	elem = (t_elem *)target_node->content;
	if (join_new_value(elem->value, new_value, &joined_value) == FAILURE)
		return (FAILURE);
	hs_update_value(&key, joined_value, target_node, env->hash->del_value);
	ft_free(new_value);
	return (SUCCESS);
}

int env_set(t_env *env, char *key, char *value, t_env_op op)
{
	t_deque_node	*target_node;

	target_node = hs_find_key(env->hash, key);
	if (target_node)
	{
		if (op == ENV_ADD)
			env_add(env, key, value, target_node);
		else if (op == ENV_JOIN)
		{
			if (env_join(env, key, value, target_node) == FAILURE)
				return (FAILURE);
		}
	}
	else
	{
		if (hs_add_to_table(env->hash, key, value) == HASH_ERROR)
			return (FAILURE);
	}
	return (SUCCESS);
}
