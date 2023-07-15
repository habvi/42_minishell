#include "ms_tokenize.h"
#include "ft_string.h"

bool	is_token_str_symbol(const char *str)
{
	const char	head_chr = *str;

	if (!(str && str[0] && ft_strchr(TOKEN_SYMBOL, head_chr)))
		return (false);
	if (str[0] == AND_CHR && str[1] != AND_CHR)
		return (false);
	return (true);
}

bool	is_token_str_quote(const char *str)
{
	const char	head_chr = *str;

	return (str && str[0] && ft_strchr(TOKEN_QUOTE, head_chr));
}

bool	is_token_str_paren(const char *str)
{
	const char	head_chr = *str;

	return (str && str[0] && ft_strchr(TOKEN_PAREN, head_chr));
}
