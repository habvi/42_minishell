#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"

void	del(void *content)
{
	free(content);
}

void	clear_hash_elem(t_elem **elem, void (*del)(void *))
{
	if (!elem || !*elem)
		return ;
	free((*elem)->key);
	(*elem)->key = NULL;
	del((*elem)->content);
	(*elem)->content = NULL;
	free(*elem);
	*elem = NULL;
}

void	clear_hash_table(t_hash **hash)
{
	size_t	idx;

	if (!hash || !*hash)
		return ;
	idx = 0;
	while (idx < (*hash)->table_size)
	{
		if ((*hash)->table[idx])
			deque_clear_all(&(*hash)->table[idx]); // TODO: clear_hash_elem
		idx++;
	}
	free((*hash)->table);
	free(*hash);
	*hash = NULL;
}
