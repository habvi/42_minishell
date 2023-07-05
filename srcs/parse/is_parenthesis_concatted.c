#include "ms_tokenize.h"
#include "ft_deque.h"

static bool	is_parenthesis_concatenated(t_token *token)
{
	const char	*token_str = token->str;

	if (is_token_str_paren(token_str) && token->concat_next)
		return (true);
	return (false);
}

bool	is_parenthesis_concatenated_all(t_deque_node *node)
{
	t_token	*token;

	while (node)
	{
		token = (t_token *)node->content;
		if (is_parenthesis_concatenated(token))
			return (false);
		node = node->next;
	}
	return (true);
}
