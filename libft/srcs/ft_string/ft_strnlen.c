#include "ft_string.h"

size_t	ft_strnlen(const char *s, const size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i])
		i++;
	return (i);
}
