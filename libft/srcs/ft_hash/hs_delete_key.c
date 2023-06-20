#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"

void	hs_delete_key(t_hash *hash, const char *key)
{
	t_deque_node	*target_node;
	uint64_t		hash_val;
	t_deque			*head;

	if (!hash || !key)
		return ;
	target_node = hs_find_key(hash, key);
	if (!target_node)
		return ;
	hash_val = hs_gen_fnv((const unsigned char *)key, hash->table_size);
	head = hash->table[hash_val];
	deque_pop_selected_node(head, target_node);
	hs_clear_deque_node(&target_node, hash->del_value);
	hash->key_count--;
}
