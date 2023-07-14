#include "ft_string.h"

char	*ft_substr_tail(char const *s, const size_t start)
{
	size_t	len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strnlen(s, start);
	if (len_s < start)
		return (ft_strdup(""));
	return (ft_strdup(s + start));
}
