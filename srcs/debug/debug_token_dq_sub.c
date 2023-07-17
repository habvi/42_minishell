#include "ms_tokenize.h"

char	*get_token_kind_str(t_token_kind kind)
{
	if (kind == TOKEN_KIND_WORD)
		return ("w");
	if (kind == TOKEN_KIND_OP_PIPE)
		return ("|");
	if (kind == TOKEN_KIND_OP_OR)
		return ("||");
	if (kind == TOKEN_KIND_OP_AND)
		return ("&&");
	if (kind == TOKEN_KIND_REDIRECT_IN)
		return ("<");
	if (kind == TOKEN_KIND_REDIRECT_HEREDOC)
		return ("<<");
	if (kind == TOKEN_KIND_REDIRECT_OUT)
		return (">");
	if (kind == TOKEN_KIND_REDIRECT_APPEND)
		return (">>");
	if (kind == TOKEN_KIND_PAREN_LEFT)
		return ("(");
	if (kind == TOKEN_KIND_PAREN_RIGHT)
		return (")");
	return ("Error");
}

char	*get_quote_str(t_quote quote)
{
	if (quote == QUOTE_SINGLE)
		return ("\'");
	if (quote == QUOTE_DOUBLE)
		return ("\"");
	if (quote == QUOTE_NONE)
		return ("");
	return ("Error");
}
