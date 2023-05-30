#include "ft_mem.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1 = (const unsigned char *)s1;
	const unsigned char	*p2 = (const unsigned char *)s2;
	size_t				i;

	if (n == 0)
		return (0);
	i = 0;
	while ((i + 1 < n) && (p1[i] == p2[i]))
		i++;
	return (p1[i] - p2[i]);
}
