#include <stddef.h>
#include "ms_builtin.h"
#include "ft_ascii.h"

static bool	is_underscore(const char c)
{
	return (c == '_');
}

static bool	is_valid_head(const char c)
{
	return (ft_isalpha(c) || is_underscore(c));
}

bool	is_valid_key(const char *word)
{
	size_t	i;
	char	c;

	if (!is_valid_head(word[0]))
		return (false);
	i = 1;
	while (word[i])
	{
		c = word[i];
		if (!(ft_isalnum(c) || is_underscore(c)))
			return (false);
		i++;
	}
	return (true);
}
