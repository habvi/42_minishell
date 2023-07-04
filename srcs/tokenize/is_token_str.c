#include "ms_tokenize.h"
#include "ft_string.h"

bool	is_token_str_symbol(char *set, char chr)
{
	return (ft_strchr(set, chr));
}

bool	is_token_str_quote(char *set, char chr)
{
	return (ft_strchr(set, chr));
}
