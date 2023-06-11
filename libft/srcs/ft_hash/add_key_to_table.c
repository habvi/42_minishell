#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_string.h"

// if malloc error, return NULL
// todo: perror?
static t_elem	*create_hash_elem(const char *key, const char *value)
{
	t_elem	*elem;

	elem = (t_elem *)malloc(sizeof(t_elem));
	if (!elem)
		return (NULL);
	elem->key = ft_strdup(key);
	if (!elem->key)
	{
		free(elem);
		return (NULL);
	}
	elem->value = ft_strdup(value);
	if (!elem->value)
	{
		free(elem->key);
		free(elem);
		return (NULL);
	}
	return (elem);
}

static int	add_elem_to_table(t_hash *hash, t_elem *elem, uint64_t hash_val)
{
	t_deque_node	*node;

	if (!hash->table[hash_val])
	{
		hash->table[hash_val] = deque_new();
		if (!hash->table[hash_val])
			return (HASH_ERROR);
	}
	node = deque_node_new(elem);
	if (!node)
		return (HASH_ERROR);
	deque_add_back(hash->table[hash_val], node);
	return (HASH_SUCCESS);
}

// if malloc error, return HASH_ERROR
// hash not freed in func
int	add_to_table(t_hash *hash, const char *elem_key, const char *elem_val)
{
	uint64_t	hash_val;
	t_elem		*elem;

	if (!elem_key)
		return (HASH_SUCCESS);
	//todo:rehash
	elem = create_hash_elem(elem_key, elem_val);
	if (!elem)
		return (HASH_ERROR);
	hash_val = generate_fnv_hash_64((unsigned char *)elem_key, hash->table_size);
	if (add_elem_to_table(hash, elem, hash_val) == HASH_ERROR)
	{
		//free key,value
		return (HASH_ERROR);
	}
	hash->key_count++;
	return (HASH_SUCCESS);
}
