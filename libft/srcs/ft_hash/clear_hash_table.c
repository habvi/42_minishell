#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

void	del_hash_elem(void *deque_content)
{
	t_elem	*elem;

	if (!deque_content)
		return ;
	elem = (t_elem *)deque_content;
	free(elem->key);
	elem->del_content(elem->content);
	free(elem);
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
			deque_clear_all(&(*hash)->table[idx], del_hash_elem);
		idx++;
	}
	free((*hash)->table);
	(*hash)->table = NULL;
	ft_free(*hash);
}
