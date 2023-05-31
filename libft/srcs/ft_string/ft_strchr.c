#include "ft_string.h"

char	*ft_strchr(const char *s, int int_c)
{
	char	c;

	c = (char)int_c;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
