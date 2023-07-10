#include "ft_string.h"

char	*ft_strchr(char *s, int int_c)
{
	char	c;

	c = (char)int_c;
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

bool	ft_strchr_bool(const char *s, int int_c)
{
	char	c;

	c = (char)int_c;
	while (*s)
	{
		if (*s == c)
			return (true);
		s++;
	}
	if (c == '\0')
		return (true);
	return (false);
}
