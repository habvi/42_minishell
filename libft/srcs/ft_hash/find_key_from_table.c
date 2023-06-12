#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_string.h"

static t_deque_node	*find_key_in_deque(t_deque_node *node, const char *key)
{
	t_elem	*elem;

	if (!node || !key)
		return (NULL);
	while (node)
	{
		elem = (t_elem *)node->content;
		if (ft_streq(elem->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_deque_node	*find_key(t_hash *hash, const char *key)
{
	uint64_t		hash_val;
	t_deque_node	*addr;

	if (!hash || !key)
		return (NULL);
	hash_val = gen_fnv_hash((const unsigned char *)key, hash->table_size);
	if (!hash->table[hash_val])
		return (NULL);
	if (!hash->table[hash_val]->size)
		return (NULL);
	addr = find_key_in_deque(hash->table[hash_val]->node, key);
	return (addr);
}
