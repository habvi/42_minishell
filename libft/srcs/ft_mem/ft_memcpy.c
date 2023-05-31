#include "ft_mem.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*pd;
	const unsigned char	*ps = (const unsigned char *)src;
	size_t				i;

	pd = (unsigned char *)dst;
	if (pd == ps)
		return (dst);
	i = 0;
	while (i < n)
	{
		pd[i] = ps[i];
		i++;
	}
	return (dst);
}
