#include "minishell.h"
#include "ft_string.h"

char	*x_ft_substr(char const *str, const size_t start, size_t len)
{
	char	*substr;

	if (!str)
		return (NULL);
	substr = ft_substr(str, start, len);
	if (!substr)
		ft_abort();
	return (substr);
}
