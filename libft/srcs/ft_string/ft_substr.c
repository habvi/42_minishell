#include "ft_string.h"

char	*ft_substr(char const *s, const size_t start, const size_t len)
{
	size_t	len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strnlen(s, start);
	if (len_s < start)
		return (ft_strdup(""));
	return (ft_strndup(s + start, len));
}
