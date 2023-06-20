#include <stdlib.h>
#include "ft_hash.h"
#include "ft_mem.h"

t_hash	*hs_create_table(uint64_t size, void (*del_value)(void *))
{
	t_hash	*hash;

	if (!del_value)
		return (NULL);
	if (!size)
		size++;
	hash = (t_hash *)malloc(sizeof(t_hash));
	if (!hash)
		return (NULL);
	hash->table_size = size;
	hash->key_count = 0;
	hash->table = (t_deque **)ft_calloc(hash->table_size, sizeof(t_deque *));
	if (!hash->table)
	{
		ft_free(hash);
		return (NULL);
	}
	hash->del_value = del_value;
	return (hash);
}
