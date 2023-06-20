#include "ft_deque.h"
#include "ft_hash.h"

// rehash
//  size *= 2

bool	is_need_rehash(t_hash *hash)
{
	if (!hash)
		return (false);
	return (true);
}

int	hs_rehash_table(t_hash *hash)
{
	(void)hash;

	return (HASH_SUCCESS);
}
