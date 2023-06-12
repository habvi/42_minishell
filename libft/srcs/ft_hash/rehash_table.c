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
		elem = node->content;
		hash_val = gen_fnv_hash((const unsigned char *)elem->key, hash_mod);
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

static void	clear_hash_table_only(t_hash *hash)
{
	size_t	idx;

	if (!hash)
		return ;
	idx = 0;
	while (idx < hash->table_size)
	{
		if (hash->table[idx])
			deque_clear_all(&hash->table[idx]);
		idx++;
	}
	ft_free(hash->table);
}

int	rehash_table(t_hash *hash)
{
	t_deque	**new_table;

	if (!hash)
		return (HASH_ERROR);
	hash->table_size *= 2;
	new_table = (t_deque **)ft_calloc(hash->table_size, sizeof(t_deque *));
	if (!new_table)
		return (HASH_ERROR);
	// just move t_deque_node. after moved, pre-table[i] remains NULL or t_deque
	if (rehash_all_to_new_table(hash, &new_table) == HASH_ERROR)
	{
		ft_free(new_table);
		return (HASH_ERROR);
	}
	// clear pre-table[i]'s t_deque. can't use clear_hash_table...(or free hash)
	clear_hash_table_only(hash);
	hash->table = new_table;
	return (HASH_SUCCESS);
}
