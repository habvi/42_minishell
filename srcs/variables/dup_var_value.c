#include "minishell.h"
#include "ft_string.h"

static int	is_operator_exist(const char c)
{
	return (c == '=');
}

// j > 0, because key exists.
// &arg[j] != NULL, len(&arg[j]) >= 0
char	*dup_var_value(const char *const arg)
{
	const size_t	len = ft_strlen(arg);
	char			*value;

	if (is_operator_exist(*(arg - 1)))
		value = x_ft_strndup(arg, len);
	else// key only
		value = NULL;
	return (value);
}
