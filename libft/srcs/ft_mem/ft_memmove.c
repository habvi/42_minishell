#include "ft_mem.h"

static void	*ft_memrcpy(void *dst, const void *src, size_t n)
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
		pd[n - i - 1] = ps[n - i - 1];
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == src)
		return (dst);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
		ft_memrcpy(dst, src, len);
	return (dst);
}
