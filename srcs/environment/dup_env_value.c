#include "minishell.h"
#include "ft_string.h"

static int	is_operator_exist(const char c)
{
	return (c == '=');
}

// j > 0, because key exists.
// &arg[j] != NULL, len(&arg[j]) >= 0
char	*dup_env_value(const char *const arg)
{
	const size_t	len = ft_strlen(arg);
	char			*value;

	if (is_operator_exist(*(arg - 1)))
	{
		value = ft_substr(arg, 0, len);
		if (!value)
			ft_abort();
	}
	else// key only
		value = NULL;
	return (value);
}
