#include <stddef.h>
#include "ft_ascii.h"

static bool	is_underscore(const char c)
{
	return (c == '_');
}

bool	is_valid_head(const char c)
{
	return (ft_isalpha(c) || is_underscore(c));
}

bool	is_valid_after_head(const char c)
{
	return (ft_isalnum(c) || is_underscore(c));
}

bool	is_valid_key(const char *word)
{
	size_t	i;

	if (!is_valid_head(word[0]))
		return (false);
	i = 1;
	while (word[i])
	{
		if (!is_valid_after_head(word[i]))
			return (false);
		i++;
	}
	return (true);
}
