#include "ft_string.h"

char	*ft_strrchr(const char *s, int int_c)
{
	char		c;
	const char	*res = NULL;

	c = (char)int_c;
	while (*s)
	{
		if (*s == c)
			res = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)res);
}
