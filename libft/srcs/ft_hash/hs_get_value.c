#include "ft_hash.h"
#include "ft_deque.h"

// if 'key' found in table, return ptr of 'value',
// otherwise, returns NULL, but value may be NULL
void	*hs_get_value(t_hash *hash, const char *key)
{
	t_deque_node	*node;
	t_elem			*elem;

	if (!hash || !key)
		return (NULL);
	node = hs_find_key(hash, key);
	if (!node)
		return (NULL);
	elem = (t_elem *)node->content;
	return (elem->value);
}
