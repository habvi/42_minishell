#include "ft_string.h"
#include "ft_sys.h"

char	*ft_strndup(const char *s, const size_t maxlen)
{
	const size_t	len_s = ft_strnlen(s, maxlen);
	char			*dst;

	dst = (char *)x_malloc(sizeof(char) * (len_s + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy_void(dst, s, len_s + 1);
	return (dst);
}
