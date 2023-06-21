#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_sys.h"

// if malloc error, return NULL
// key != NULL
static t_elem	*create_hash_elem(char *key, void *value)
{
	t_elem	*elem;

	elem = (t_elem *)x_malloc(sizeof(t_elem));
	if (!elem)
		return (NULL);
	elem->key = key;
	elem->value = value;
	return (elem);
}

// hash != NULL
int	hs_alloc_deque_head(t_deque **table, uint64_t hash_val)
{
	if (table[hash_val])
		return (HASH_SUCCESS);
	table[hash_val] = deque_new();
	if (!table[hash_val])
		return (HASH_ERROR);
	return (HASH_SUCCESS);
}

// if deque_node_new malloc error, remain head t_deque(-> free hs_clear_table)
// hash != NULL, elem != NULL
static int	add_elem_to_table(t_hash *hash, t_elem *elem, uint64_t hash_val)
{
	t_deque_node	*node;

	node = deque_node_new(elem);
	if (!node)
		return (HASH_ERROR);
	deque_add_back(hash->table[hash_val], node);
	return (HASH_SUCCESS);
}

// hash != NULL, key != NULL
int	hs_add_to_table(t_hash *hash, char *key, void *value)
{
	t_elem		*elem;
	uint64_t	hash_val;

	if (is_need_rehash(hash) && hs_rehash_table(hash) == HASH_ERROR)
		return (HASH_ERROR); // free hash by user
	hash_val = hs_gen_fnv((const unsigned char *)key, hash->table_size);
	if (hs_alloc_deque_head(hash->table, hash_val) == HASH_ERROR)
		return (HASH_ERROR);
	elem = create_hash_elem(key, value);
	if (!elem)
		return (HASH_ERROR);
	if (add_elem_to_table(hash, elem, hash_val) == HASH_ERROR)
	{
		hs_clear_elem(&elem, hash->del_value);
		return (HASH_ERROR);
	}
	hash->key_count++;
	return (HASH_SUCCESS);
}

// if malloc error, return HASH_ERROR
// hash not freed in func
// 'key' cannot be null, 'value' can accept null
int	hs_set_key(t_hash *hash, char *key, void *value)
{
	t_deque_node	*target_node;

	if (!hash || !key)
		return (HASH_ERROR);
	target_node = hs_find_key(hash, key);
	if (target_node)
		hs_update_value(&key, value, target_node, hash->del_value);
	else
	{
		if (hs_add_to_table(hash, key, value) == HASH_ERROR)
			return (HASH_ERROR);
	}
	return (HASH_SUCCESS);
}
