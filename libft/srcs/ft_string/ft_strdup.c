#include "ft_string.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	len_s;
	char	*dst;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	dst = (char *)malloc(sizeof(char) * (len_s + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s, len_s + 1);
	return (dst);
}
