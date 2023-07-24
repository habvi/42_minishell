#include "ms_parse.h"
#include "ft_deque.h"

t_node_kind	convert_kind_token_to_node(const t_deque_node *token_node)
{
	t_token			*token;
	t_token_kind	token_kind;

	if (!token_node)
		return (NODE_KIND_NONE);
	token = token_node->content;
	token_kind = token->kind;
	if (token_kind == TOKEN_KIND_OP_PIPE)
		return (NODE_KIND_OP_PIPE);
	if (token_kind == TOKEN_KIND_OP_OR)
		return (NODE_KIND_OP_OR);
	if (token_kind == TOKEN_KIND_OP_AND)
		return (NODE_KIND_OP_AND);
	if (token_kind == TOKEN_KIND_PAREN_LEFT)
		return (NODE_KIND_SUBSHELL);
	if (token_kind == TOKEN_KIND_PAREN_RIGHT)
		return (NODE_KIND_SUBSHELL);
	if (token_kind == TOKEN_KIND_WORD)
		return (NODE_KIND_COMMAND);
	return (NODE_KIND_NONE);
}
