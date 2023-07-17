#include "ms_tokenize.h"
#include "ft_deque.h"

bool	is_token_kind_paren_left_as_ast_node(const t_deque_node *node)
{
	t_token			*token;
	t_token_kind	kind;

	if (!node)
		return (false);
	token = (t_token *)node->content;
	kind = token->kind;
	return (kind == TOKEN_KIND_PAREN_LEFT);
}

bool	is_token_kind_paren_right_as_ast_node(const t_deque_node *node)
{
	t_token			*token;
	t_token_kind	kind;

	if (!node)
		return (false);
	token = (t_token *)node->content;
	kind = token->kind;
	return (kind == TOKEN_KIND_PAREN_RIGHT);
}

bool	is_token_kind_subshell_as_ast_node(const t_deque_node *node)
{
	if (is_token_kind_paren_left_as_ast_node(node))
		return (true);
	if (is_token_kind_paren_right_as_ast_node(node))
		return (true);
	return (false);
}
