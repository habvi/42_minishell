#include "minishell.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_string.h"

// todo: fatal error

// key=
static void	env_add(t_env *env, char *key, char *value, t_deque_node *node)
{
	if (!value)
	{
		ft_free(&key);
		return ;
	}
	hs_update_value(&key, value, node, env->hash->del_value);
}

static char	*join_new_value(char *pre, char *new)
{
	char	*joined;

	joined = ft_strjoin(pre, new);
	if (!joined)
		ft_abort();
	return (joined);
}

// key expected `name` -> void ...?
// key+=
static void	env_join(t_env *env, char *key, char *new_value, t_deque_node *node)
{
	t_elem	*elem;
	char	*joined_value;

	elem = (t_elem *)node->content;
	joined_value = join_new_value(elem->value, new_value);
	hs_update_value(&key, joined_value, node, env->hash->del_value);
	ft_free(&new_value);
}

void	env_set(t_env *env, char *key, char *value, t_env_op op)
{
	t_deque_node	*target_node;

	target_node = hs_find_key(env->hash, key);
	if (target_node)
	{
		if (op == ENV_ADD)
			env_add(env, key, value, target_node);
		else if (op == ENV_JOIN)
			env_join(env, key, value, target_node);
	}
	else
	{
		if (hs_add_to_table(env->hash, key, value) == HASH_ERROR)
			ft_abort();
	}
}
