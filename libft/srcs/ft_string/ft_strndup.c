#include "ft_string.h"
#include <stdlib.h>

char	*ft_strndup(const char *s, size_t maxlen)
{
	const size_t	len_s = ft_strnlen(s, maxlen);
	char			*dst;

	dst = (char *)malloc(sizeof(char) * (len_s + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy_void(dst, s, len_s + 1);
	return (dst);
}
