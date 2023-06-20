#include "ft_hash.h"
#include "ft_deque.h"

// if 'key' found in table, return ptr of 'content',
// otherwise, returns NULL, but content may be NULL
void	*hs_get_value(t_hash *hash, const char *key)
{
	t_deque_node	*node;
	t_elem			*elem;

	if (!hash || !key)
		return (NULL);
	node = hs_find_key(hash, key);
	if (!node)
		return (NULL);
	elem = node->content;
	return (elem->content);
}
