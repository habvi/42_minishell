#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_string.h"

static bool	is_key_in_deque(t_deque_node *node, const char *key)
{
	t_elem	*elem;

	if (!node || !key)
		return (NULL);
	while (node)
	{
		elem = (t_elem *)node->content;
		if (ft_streq(elem->key, key))
			return (true);
		node = node->next;
	}
	return (false);
}

// return true if key is in table
bool	find_key(t_hash *hash, const char *key)
{
	uint64_t	hash_val;
	bool		result;

	if (!hash || !key)
		return (false);
	hash_val = generate_fnv_hash_64((unsigned char *)key, hash->table_size);
	if (!hash->table[hash_val])
		return (false);
	if (!hash->table[hash_val]->size)
		return (false);
	result = is_key_in_deque(hash->table[hash_val]->node, key);
	return (result);
}
