#include <stdlib.h>

void	*ft_free(void **ptr)
{
	if (!ptr)
		return (NULL);
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

void	*free_2d_array(char ***ptr)
{
	size_t	i;

	if (!*ptr)
		return (NULL);
	i = 0;
	while ((*ptr)[i])
	{
		ft_free((void **)&(*ptr)[i]);
		i++;
	}
	ft_free((void **)ptr);
	return (NULL);
}
