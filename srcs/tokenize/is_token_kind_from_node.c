#include "ms_tokenize.h"
#include "ft_deque.h"

bool	is_token_kind_and_or_from_node(t_deque_node *node)
{
	t_token			*token;
	t_token_kind	kind;

	if (!node)
		return (false);
	token = (t_token *)node->content;
	kind = token->kind;
	return (kind == TOKEN_KIND_OP_AND || kind == TOKEN_KIND_OP_OR);
}

bool	is_token_kind_pipe_from_node(t_deque_node *node)
{
	t_token			*token;
	t_token_kind	kind;

	if (!node)
		return (false);
	token = (t_token *)node->content;
	kind = token->kind;
	return (kind == TOKEN_KIND_OP_PIPE);
}

bool	is_token_kind_command_as_ast_node(t_deque_node *node)
{
	t_token			*token;
	t_token_kind	kind;

	if (!node)
		return (false);
	token = (t_token *)node->content;
	kind = token->kind;
	if (is_token_kind_word(kind))
		return (true);
	if (is_token_kind_redirection(kind))
		return (true);
	return (false);
}
