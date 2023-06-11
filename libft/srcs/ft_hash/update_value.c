#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_string.h"

// key exist in hash
// free(key, pre-content), update new content
void	update_content_of_key(t_hash *hash, char *key, void *content)
{
	uint64_t		hash_val;
	t_deque_node	*node;
	t_elem			*elem;

	hash_val = generate_fnv_hash_64((unsigned char *)key, hash->table_size);
	node = hash->table[hash_val]->node;
	while (node)
	{
		elem = (t_elem *)node->content;
		if (ft_streq(elem->key, key))
		{
			// free(key);
			// todo: del func
			// free(node->content);
			elem->content = content;
			return ;
		}
		node = node->next;
	}
}
