#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

static void	create_matched_tokens_each(t_deque_node *node, t_deque *matched_tokens)
{
	t_token	*token;

	token = (t_token *)node->content;
	if (token->quote != QUOTE_NONE)
		deque_add_back(matched_tokens, node);
	else
	{
		pattern_matching_and_add(token->str, matched_tokens);
		deque_clear_node(&node, del_token);
	}
}

static t_deque	*create_matched_tokens_all(t_deque *tokens)
{
	t_deque			*matched_tokens;
	t_deque_node	*node;

	matched_tokens = deque_new();
	if (!matched_tokens)
		ft_abort();
	while (!deque_is_empty(tokens))
	{
		node = deque_pop_front(tokens);
		create_matched_tokens_each(node, matched_tokens);
	}
	return (matched_tokens);
}

void	expand_wildcard(t_deque **tokens)
{
	t_deque	*matched_tokens;

	if (!*tokens)
		return ;
	matched_tokens = create_matched_tokens_all(*tokens);
	deque_clear_all(tokens, del_token);
	*tokens = matched_tokens;
}
