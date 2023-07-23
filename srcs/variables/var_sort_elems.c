#include "ft_hash.h"
#include "ft_string.h"

static void	swap_elems(t_elem **elems, const size_t i, const size_t j)
{
	t_elem	*tmp;

	tmp = elems[i];
	elems[i] = elems[j];
	elems[j] = tmp;
}

// sort to ascending
// i <-> j
void	var_sort_elems_by_key(t_elem **elems)
{
	size_t	i;
	size_t	j;
	char	*key_i;
	char	*key_j;

	i = 0;
	while (elems[i])
	{
		j = i;
		while (elems[j])
		{
			key_i = elems[i]->key;
			key_j = elems[j]->key;
			if (i != j && ft_strcmp(key_i, key_j) > 0)
				swap_elems(elems, i, j);
			j++;
		}
		i++;
	}
}
