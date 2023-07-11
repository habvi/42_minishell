#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"

static void	create_split_tokens_each(t_deque_node *node, \
										t_deque *expanded, \
										bool is_assign_cmd)
{
	t_token	*token;

	token = (t_token *)node->content;
	if (token->quote != QUOTE_NONE)
		deque_add_back(expanded, node);
	else if (is_assign_cmd)
	{
		word_split_and_add_for_assign_cmd(token->str, expanded, is_assign_cmd);
		deque_clear_node(&node, del_token);
	}
	else
	{
		word_split_and_add_for_general_cmd(token->str, expanded);
		deque_clear_node(&node, del_token);
	}
}

// tokens -> split
// command ?
//  *export, declare
//  *others
static t_deque	*create_split_tokens_all(t_deque *tokens, bool is_assign_cmd)
{
	t_deque			*expanded_tokens;
	t_deque_node	*node;

	expanded_tokens = deque_new();
	if (!expanded_tokens)
		ft_abort();
	while (!deque_is_empty(tokens))
	{
		node = deque_pop_front(tokens);
		create_split_tokens_each(node, expanded_tokens, is_assign_cmd);
	}
	return (expanded_tokens);
}

// tokens=[token1]=[token2]-[token3]=[token4]
//    ->  [token1token2]-[token3token4]
// if concat_next=true; next token exist
void	split_expand_word(t_deque **tokens, bool is_assign_cmd)
{
	t_deque	*expanded;

	if (!*tokens)
		return ;
	expanded = create_split_tokens_all(*tokens, is_assign_cmd);
	deque_clear_all(tokens, del_token);
	*tokens = expanded;
}
