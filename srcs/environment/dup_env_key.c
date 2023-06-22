#include "minishell.h"
#include "ft_string.h"

static size_t	get_key_len(const char *const s)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		if (s[len] == '=')
			break ;
		if (s[len] == '+' && s[len + 1] == '=')
			break ;
		len++;
	}
	return (len);
}

// abc=ddd     =       abc+=def
// 0123        0       01234
//    ^len     ^len       ^len

//  malloc error -> return (PROCESS_ERROR)
int	dup_env_key(const char *const arg, char **key, size_t *len)
{
	*len = get_key_len(arg);
	*key = ft_substr(arg, 0, *len);
	if (!*key)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
