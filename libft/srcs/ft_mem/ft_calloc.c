#include "ft_mem.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*head;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	total = size * count;
	if (total / size != count)
		return (NULL);
	head = (void *)malloc(total);
	if (head == NULL)
		return (NULL);
	ft_bzero(head, total);
	return (head);
}
