#include "minishell.h"
#include "ft_deque.h"
#include "ft_hash.h"

bool	is_key_exist(t_env *env, const char *key)
{
	t_deque_node	*node;

	node = hs_find_key(env->hash, key);
	if (!node)
		return (false);
	return (true);
}
