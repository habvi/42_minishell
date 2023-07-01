#include "minishell.h"
#include "ft_string.h"

char	*x_ft_strdup(const char *str)
{
	char	*dup;

	if (!str)
		return (NULL);
	dup = ft_strdup(str);
	if (!dup)
		ft_abort();
	return (dup);
}
