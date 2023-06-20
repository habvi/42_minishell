#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

// rehash
//  size *= 2

bool	is_need_rehash(t_hash *hash)
{
	if (!hash)
		return (false);
	return (true);
}

static int	rehash_all_node(t_deque_node *node, \
							t_deque ***new_table, \
							size_t hash_mod)
{
	t_elem		*elem;
	uint64_t	hash_val;

	while (node)
	{
		// elem != NULL?
		elem = (t_elem *)node->content;
		hash_val = hs_gen_fnv((const unsigned char *)elem->key, hash_mod);
		//todo:only move&add to (*new_table)[hash_val]. can't use set_to_table..
		(void)hash_val;
		(void)new_table;
		node = node->next;
	}
	return (HASH_SUCCESS);
}

static int	rehash_all_to_new_table(t_hash *hash, t_deque ***new_table)
{
	size_t			i;
	t_deque_node	*head_node;

	i = 0;
	while (i < hash->table_size)
	{
		if (hash->table[i] && hash->table[i]->size)
		{
			head_node = hash->table[i]->node;
			if (rehash_all_node(head_node, new_table, hash->table_size) \
																== HASH_ERROR)
			{
				//todo:free all new_table
				return (HASH_ERROR);
			}
		}
		i++;
	}
	return (HASH_SUCCESS);
}

int	hs_rehash_table(t_hash *hash)
{
	t_deque	**new_table;
	size_t	new_table_size;

	if (!hash)
		return (HASH_ERROR);
	// overflow check
	new_table_size = hash->table_size * 2;
	new_table = (t_deque **)ft_calloc(new_table_size, sizeof(t_deque *));
	if (!new_table)
		return (HASH_ERROR);
	if (rehash_all_to_new_table(hash, &new_table) == HASH_ERROR)
	{
		hs_clear_table(new_table, new_table_size, hash->del_value);
		return (HASH_ERROR);
	}
	hs_clear_table(hash->table, hash->table_size, hash->del_value);
	hash->table_size = new_table_size;
	hash->table = new_table;
	return (HASH_SUCCESS);
}
