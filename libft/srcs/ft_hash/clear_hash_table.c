#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"

//void	clear_hash_elem(t_elem **elem, void (*del)(void *))
//{
//	if (!elem || !*elem)
//		return ;
//	free((*elem)->key);
//	del((*elem)->content);
//	free(*elem);
//	*elem = NULL;
//}

void	clear_hash_table(t_hash **hash)
{
	(void)hash;
	size_t	idx;

	if (!hash || !*hash)
		return ;
	idx = 0;
	while (idx < (*hash)->table_size)
	{
		if ((*hash)->table[idx])
			deque_clear_all(&(*hash)->table[idx]); // TODO: del(content)
		idx++;
	}
	free((*hash)->table);
	free(*hash);
	*hash = NULL;
}
