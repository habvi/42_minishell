#include "ms_tokenize.h"
#include "ft_deque.h"

t_token_kind	get_token_kind(t_deque_node *token_node)
{
	const t_token	*token = (t_token *)token_node->content;

	return (token->kind);
}
