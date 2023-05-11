#include <stdlib.h>
#include "ft_string.h"

void	*free_all(char **split_strs)
{
	size_t	i;

	i = 0;
	while (split_strs[i] != NULL)
	{
		free(split_strs[i]);
		i++;
	}
	free(split_strs);
	return (NULL);
}
