#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_sys.h"

// if malloc error, return NULL
static t_elem	*create_hash_elem(char *key, void *content)
{
	t_elem	*elem;

	elem = (t_elem *)x_malloc(sizeof(t_elem));
	if (!elem)
		return (NULL);
	elem->key = key;
	elem->content = content;
	return (elem);
}

static int	alloc_hash_val_index_of_table(t_hash *hash, uint64_t hash_val)
{
	if (!hash->table[hash_val])
	{
		hash->table[hash_val] = deque_new();
		if (!hash->table[hash_val])
			return (HASH_ERROR);
	}
	return (HASH_SUCCESS);
}

// if deque_node_new malloc error, remain head t_deque(-> free clear_hash_table)
static int	add_elem_to_table(t_hash *hash, t_elem *elem, uint64_t hash_val)
{
	t_deque_node	*node;

	node = deque_node_new(elem);
	if (!node)
		return (HASH_ERROR);
	deque_add_back(hash->table[hash_val], node);
	return (HASH_SUCCESS);
}

static int	add_to_table(t_hash *hash, \
							char *key, \
							void *content, \
							void (*del_content)(void *))
{
	t_elem			*elem;
	uint64_t		hash_val;

	if (is_need_rehash(hash) && rehash_table(hash) == HASH_ERROR)
		return (HASH_ERROR); // free hash by user
	hash_val = gen_fnv_hash((const unsigned char *)key, hash->table_size);
	if (alloc_hash_val_index_of_table(hash, hash_val) == HASH_ERROR)
		return (HASH_ERROR);
	elem = create_hash_elem(key, content);
	if (!elem)
		return (HASH_ERROR);
	if (add_elem_to_table(hash, elem, hash_val) == HASH_ERROR)
	{
		clear_hash_elem(&elem, del_content);
		return (HASH_ERROR);
	}
	return (HASH_SUCCESS);
}

// if malloc error, return HASH_ERROR
// hash not freed in func
// 'key' cannot be null, 'value' can accept null
int	set_to_table(t_hash *hash, char *key, \
					void *content, \
					void (*del_content)(void *))
{
	t_deque_node	*target_node;

	if (!key)
		return (HASH_SUCCESS);
	target_node = find_key(hash, key);
	if (target_node)
		update_content_of_key(&key, content, target_node, del_content);
	else
	{
		if (add_to_table(hash, key, content, del_content) == HASH_ERROR)
			return (HASH_ERROR);
		hash->key_count++;
	}
	return (HASH_SUCCESS);
}
