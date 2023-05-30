#include "ft_mem.h"

void	*ft_memchr(const void *s, int int_c, size_t n)
{
	const unsigned char	*ps = (const unsigned char *)s;
	unsigned char		c;
	size_t				i;

	c = (unsigned char)int_c;
	i = 0;
	while (i < n)
	{
		if (ps[i] == c)
			return ((void *)&ps[i]);
		i++;
	}
	return (NULL);
}
