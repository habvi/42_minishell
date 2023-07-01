#include "minishell.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_hash.h"

int	env_is_key_exist(t_var *var, const char *key)
{
	t_deque_node	*node;

	node = hs_find_key(var->hash, key);
	if (!node)
		return (false);
	return (true);
}
