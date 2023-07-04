#include "ms_tokenize.h"
#include "ft_string.h"

bool	is_token_str_symbol(char chr)
{
	return (ft_strchr(TOKEN_SYMBOL, chr));
}

bool	is_token_str_quote(char chr)
{
	return (ft_strchr(TOKEN_QUOTE, chr));
}

bool	is_token_str_paren(char chr)
{
	return (ft_strchr(TOKEN_PAREN, chr));
}
