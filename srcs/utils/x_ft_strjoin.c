#include "minishell.h"
#include "ft_string.h"

char	*x_ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
		ft_abort();
	return (join);
}
