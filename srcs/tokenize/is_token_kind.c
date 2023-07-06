#include "ms_tokenize.h"
#include "ft_deque.h"

bool	is_token_kind_and_or(t_deque_node *node)
{
	t_token			*token;
	t_token_kind	kind;

	if (!node)
		return (false);
	token = (t_token *)node->content;
	kind = token->kind;
	return (kind == TOKEN_KIND_OP_AND || kind == TOKEN_KIND_OP_OR);
}

bool	is_token_kind_pipe(t_deque_node *node)
{
	t_token			*token;
	t_token_kind	kind;

	if (!node)
		return (false);
	token = (t_token *)node->content;
	kind = token->kind;
	return (kind == TOKEN_KIND_OP_PIPE);
}

bool	is_token_kind_subshell(t_deque_node *node)
{
	t_token			*token;
	t_token_kind	kind;

	if (!node)
		return (false);
	token = (t_token *)node->content;
	kind = token->kind;
	return (kind == TOKEN_KIND_PAREN_LEFT || kind == TOKEN_KIND_PAREN_RIGHT);
}

bool	is_token_kind_word(t_deque_node *node)
{
	t_token			*token;
	t_token_kind	kind;

	if (!node)
		return (false);
	token = (t_token *)node->content;
	kind = token->kind;
	return (kind == TOKEN_KIND_WORD);
}

bool	is_token_kind_redirection(t_token_kind token_kind)
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
