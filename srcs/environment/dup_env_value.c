#include "minishell.h"
#include "ft_string.h"

static int	is_operator_exist(const char c)
{
	return (c == '=');
}

// j > 0, because key exists.
// &arg[j] != NULL, len(&arg[j]) >= 0

//  malloc error -> return (PROCESS_ERROR)
int	dup_env_value(const char *const arg, char **value)
{
	const size_t	len = ft_strlen(arg);

	if (is_operator_exist(*(arg - 1)))
	{
		*value = ft_substr(arg, 0, len);
		if (!*value)
			return (PROCESS_ERROR);
	}
	else// key only
		*value = NULL;
	return (SUCCESS);
}
