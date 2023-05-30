#include "ft_string.h"

size_t	count_2d_array(const char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
