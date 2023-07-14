#include "ms_tokenize.h"
#include "ft_deque.h"

bool	is_token_kind_word(const t_token_kind token_kind)
{
	return (token_kind == TOKEN_KIND_WORD);
}

bool	is_token_kind_redirection(const t_token_kind token_kind)
{
	if (token_kind == TOKEN_KIND_REDIRECT_IN)
		return (true);
	if (token_kind == TOKEN_KIND_REDIRECT_HEREDOC)
		return (true);
	if (token_kind == TOKEN_KIND_REDIRECT_OUT)
		return (true);
	if (token_kind == TOKEN_KIND_REDIRECT_APPEND)
		return (true);
	return (false);
}
