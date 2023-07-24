#include "minishell.h"
#include "ft_string.h"

char	**x_ft_split(char const *str, char c)
{
	char	**split_str;

	if (!str)
		return (NULL);
	split_str = ft_split(str, c);
	if (!split_str)
		ft_abort();
	return (split_str);
}
