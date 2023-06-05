#include <stdlib.h>
#include "ft_string.h"

void	*free_2d_array(char ***ptr)
{
	size_t	i;

	if (!*ptr)
		return (NULL);
	i = 0;
	while ((*ptr)[i])
	{
		free((*ptr)[i]);
		(*ptr)[i] = NULL;
		i++;
	}
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}
