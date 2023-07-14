#include "ft_gnl_inter.h"

static void	ft_strlcpy_for_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
}

char	*ft_substr_for_gnl(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (s == NULL)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy_for_gnl(res, s + start, len + 1);
	return (res);
}

void	*ft_memmove_for_gnl(void *dst, const void *src, size_t len)
{
	unsigned char		*pd;
	const unsigned char	*ps = (const unsigned char *)src;
	size_t				i;

	if (dst == src)
		return (dst);
	pd = (unsigned char *)dst;
	i = 0;
	while (i < len)
	{
		if (dst < src)
			pd[i] = ps[i];
		else
			pd[len - i - 1] = ps[len - i - 1];
		i++;
	}
	return (dst);
}
