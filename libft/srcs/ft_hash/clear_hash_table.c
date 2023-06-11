#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"

void	clear_hash_elem(t_elem **elem)
{
	if (!elem || !*elem)
		return ;
	free((*elem)->key);
	free((*elem)->value);
	free(*elem);
	*elem = NULL;
}

void	clear_hash_table(t_hash **hash)
{
	(void)hash;
}
