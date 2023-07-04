#include "ms_tokenize.h"
#include "ft_string.h"

//todo: str??
bool	is_token_str_symbol(const char *str)
{
	const char	head_chr = *str;

	return (ft_strchr(TOKEN_SYMBOL, head_chr));
}

bool	is_token_str_quote(const char *str)
{
	const char	head_chr = *str;

	return (ft_strchr(TOKEN_QUOTE, head_chr));
}

bool	is_token_str_paren(const char *str)
{
	const char	head_chr = *str;

	return (ft_strchr(TOKEN_PAREN, head_chr));
}
