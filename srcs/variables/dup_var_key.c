#include "minishell.h"

static bool	is_add_operator(const char c)
{
	return (c == '=');
}

static bool	is_join_operator(const char *const sub_s)
{
	return (sub_s[0] == '+' && sub_s[1] == '=');
}

static size_t	get_key_len(const char *const s)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		if (is_add_operator(s[len]))
			break ;
		if (is_join_operator(&s[len]))
			break ;
		len++;
	}
	return (len);
}

// abc=ddd     =       abc+=def
// 0123        0       01234
//    ^len     ^len       ^len
// arg != NULL
char	*dup_var_key(const char *const arg, size_t *len)
{
	char	*key;

	*len = get_key_len(arg);
	key = x_ft_substr(arg, 0, *len);
	return (key);
}
