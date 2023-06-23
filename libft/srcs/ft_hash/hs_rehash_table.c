#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

// hash != NULL
bool	is_need_rehash(t_hash *hash)
{
	const double	ratio = hash->key_count / (double)hash->table_size * 100;

	return (ratio >= LOAD_FACTOR_LIMIT_PCT);
}

static size_t	get_new_table_size(const size_t table_size)
{
	if (table_size > SIZE_MAX / 2)
		return (table_size);
	return (table_size * 2);
}

// deque != NULL
static int	move_elem_to_new(t_deque *deque, \
							t_deque **new_table, \
							const size_t hash_mod)
{
	t_deque_node	*node;
	t_elem			*elem;
	size_t			hash_val;

	while (!deque_is_empty(deque))
	{
		node = deque_pop_front(deque);
		elem = (t_elem *)node->content;
		hash_val = hs_gen_fnv((const unsigned char *)elem->key, hash_mod);
		if (hs_alloc_deque_head(new_table, hash_val) == HASH_ERROR)
		{
			deque_add_back(deque, node);
			return (HASH_ERROR);
		}
		deque_add_back(new_table[hash_val], node);
	}
	return (HASH_SUCCESS);
}

static int	move_all_elem_to_new(t_hash *hash, \
								t_deque **new_table, \
								const size_t new_table_size)
{
	size_t	i;

	i = 0;
	while (i < hash->table_size)
	{
		if (!hash->table[i] || !hash->table[i]->size)
		{
			i++;
			continue ;
		}
		if (move_elem_to_new(hash->table[i], new_table, new_table_size) \
															== HASH_ERROR)
		{
			return (HASH_ERROR);
		}
		i++;
	}
	return (HASH_SUCCESS);
}

int	hs_rehash_table(t_hash *hash)
{
	const size_t	new_table_size = get_new_table_size(hash->table_size);
	t_deque			**new_table;

	if (!hash)
		return (HASH_ERROR);
	new_table = (t_deque **)ft_calloc(new_table_size, sizeof(t_deque *));
	if (!new_table)
		return (HASH_ERROR);
	if (move_all_elem_to_new(hash, new_table, new_table_size) == HASH_ERROR)
	{
		hs_clear_table(new_table, new_table_size, hash->del_value);
		return (HASH_ERROR);
	}
	hs_clear_table(hash->table, hash->table_size, hash->del_value);
	hash->table_size = new_table_size;
	hash->table = new_table;
	return (HASH_SUCCESS);
}
