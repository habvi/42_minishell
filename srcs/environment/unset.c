#include "minishell.h"
#include "ft_hash.h"

// unset failure case ...? void ?
int	env_unset(t_env *env, char *key)
{
	t_deque_node	*node;

	node = hs_find_key(env->hash, (const char *)key);
	if (!node)
		return (SUCCESS);
	return (SUCCESS);
}
