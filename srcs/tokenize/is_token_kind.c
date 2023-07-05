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
