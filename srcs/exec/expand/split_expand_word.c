#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_string.h"

static void	create_split_tokens_each(t_deque_node *node, t_deque *expanded)
{
	t_token	*token;
	char	*str_in_delim;

	token = (t_token *)node->content;
	str_in_delim = ft_find_set_in_str(token->str, TOKEN_DELIM);
	if (token->quote == QUOTE_SINGLE || token->quote == QUOTE_DOUBLE)
		deque_add_back(expanded, node);
	else if (ft_streq(str_in_delim, "\0"))
		deque_add_back(expanded, node);
	else
	{
		word_split_and_add(token->str, expanded, token->concat_next);
		deque_clear_node(&node, del_token);
	}
}

// tokens -> split
// command ?
//  *export, declare
//  *others
static t_deque	*create_split_tokens_all(t_deque *tokens)
{
	t_deque			*expanded_tokens;
	t_deque_node	*node;

	expanded_tokens = deque_new();
	if (!expanded_tokens)
		ft_abort();
	while (!deque_is_empty(tokens))
	{
		node = deque_pop_front(tokens);
		create_split_tokens_each(node, expanded_tokens);
	}
	return (expanded_tokens);
}

// tokens=[word1  word2]
//    ->  [word1]-[word2]
void	split_expand_word(t_deque **tokens)
{
	t_deque	*expanded;

	if (!*tokens)
		return ;
	expanded = create_split_tokens_all(*tokens);
	deque_clear_all(tokens, del_token);
	*tokens = expanded;
}
