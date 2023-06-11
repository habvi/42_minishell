#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"

// if malloc error, return NULL
// todo: perror?
static t_elem	*create_hash_elem(char *key, void *content)
{
	t_elem	*elem;

	elem = (t_elem *)malloc(sizeof(t_elem));
	if (!elem)
		return (NULL);
	elem->key = key;
	elem->content = content;
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
// 'key' cannot be null, 'value' can accept null
int	set_to_table(t_hash *hash, char *key, void *content)
{
	uint64_t	hash_val;
	t_elem		*elem;

	if (!key)
		return (HASH_SUCCESS);
	if (find_key(hash, key))
		update_content_of_key(hash, key, content);
	else
	{
		elem = create_hash_elem(key, content);
		if (!elem)
			return (HASH_ERROR);
		hash_val = generate_fnv_hash_64((unsigned char *)key, hash->table_size);
		if (add_elem_to_table(hash, elem, hash_val) == HASH_ERROR)
		{
			free(key);
			// todo: del func
			free(content);
			free(elem);
			return (HASH_ERROR);
		}
		hash->key_count++;
	}
	//todo:rehash
	return (HASH_SUCCESS);
}
