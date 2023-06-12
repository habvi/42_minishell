#include <stdlib.h>
#include "ft_string.h"

static void	*ft_free_sub(void **ptr)
{
    free(*ptr);
    *ptr = NULL;
	return (NULL);
}

void	*ft_free(void *ptr)
{
    if (!ptr)
      return (NULL);
	return (ft_free_sub(&ptr));
}

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
