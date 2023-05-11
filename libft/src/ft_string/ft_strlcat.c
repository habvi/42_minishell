#include "ft_string.h"
#include "ft_math.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	size;

	if (dst == NULL)
		len_dst = 0;
	else
		len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	size = ft_min(len_src, dstsize - len_dst - 1);
	ft_strlcpy(dst + len_dst, src, size + 1);
	return (len_dst + len_src);
}
