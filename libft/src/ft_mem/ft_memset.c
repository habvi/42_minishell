#include "ft_mem.h"

void	*ft_memset(void *b, int int_c, size_t len)
{
	unsigned char	*pb;
	unsigned char	c;
	size_t			i;

	pb = (unsigned char *)b;
	c = (unsigned char)int_c;
	i = 0;
	while (i < len)
	{
		pb[i] = c;
		i++;
	}
	return (b);
}
