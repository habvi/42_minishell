#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_string.h"

// *node != NULL
static void	remove_empty_tokens_each(t_deque *tokens, t_deque_node **node)
{
	t_deque_node	*next;
	t_token			*token;

	token = (t_token *)(*node)->content;
	next = (*node)->next;
	if (ft_strlen(token->str) > 0)
	{
		*node = next;
		return ;
	}
	deque_pop_selected_node(tokens, *node);
	deque_clear_node(node, del_token);
	*node = next;
}

// tokens=[token1]-[]-["aa"]-['a']
//                 ^^remove
void	remove_empty_tokens(t_deque *tokens)
{
	t_token			*token;
	t_deque_node	*node;

	if (!tokens)
		return ;
	node = tokens->node;
	while (node)
	{
		token = (t_token *)node->content;
		if (token->quote != QUOTE_NONE)
		{
			node = node->next;
			continue ;
		}
		remove_empty_tokens_each(tokens, &node);
	}
}
