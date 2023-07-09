#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"

static char	*concat_token_str(t_deque_node *node1, t_deque_node *node2)
{
	const t_token	*token1 = (t_token *)node1->content;;
	const t_token	*token2 = (t_token *)node2->content;;
	char			*concat_str;

	concat_str = x_ft_strjoin(token1->str, token2->str);
	return (concat_str);
}

static void	swap_next_token_str(t_deque_node *next, char *concat_str)
{
	t_token	*next_token;

	next_token = (t_token *)next->content;
	ft_free(&next_token->str);
	next_token->str = concat_str;
}

// tokens=[token1]=[token2]-[token3]=[token4]
//         ^now   ^ concat_next
// *node != NULL
void	concat_tokens_each(t_deque *tokens, t_deque_node **node)
{
	t_deque_node	*next;
	char			*concat_str;

	next = (*node)->next;
	concat_str = concat_token_str(*node, next);
	swap_next_token_str(next, concat_str);
	deque_pop_selected_node(tokens, *node);
	deque_clear_node(node, del_token);
	*node = next;
}

// tokens=[token1]=[token2]-[token3]=[token4]
//    ->  [token1token2]-[token3token4]
// if concat_next=true; next token exist
void	concat_tokens(t_deque *tokens)
{
	t_token			*token;
	t_deque_node	*node;

	if (!tokens)
		return ;
	node = tokens->node;
	while (node)
	{
		token = (t_token *)node->content;
		if (!token->concat_next)
		{
			node = node->next;
			continue ;
		}
		concat_tokens_each(tokens, &node);
	}
}
