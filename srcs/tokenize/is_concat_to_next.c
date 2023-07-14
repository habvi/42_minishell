#include "ms_tokenize.h"
#include "ft_string.h"

static bool	is_token_str_word(char token_head)
{
	return (!ft_strchr(TOKEN_SYMBOL TOKEN_PAREN TOKEN_DELIM, token_head));
}

// ((
static bool	is_concatted_paren(char token_head, char next_chr)
{
	if (ft_strchr(TOKEN_PAREN, token_head) && token_head == next_chr)
		return (true);
	return (false);
}

// token_str is word = !(symbol && paren)
//     &&
// next is word
bool	is_concat_to_next(char token_head, char next_chr)
{
	if (is_token_str_word(token_head) && is_token_str_word(next_chr))
		return (true);
	if (is_concatted_paren(token_head, next_chr))
		return (true);
	return (false);
}
