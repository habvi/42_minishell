#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_string.h"

static bool	is_wildcard_in_token(const char *str)
{
	return (ft_strchr_bool(str, '*')); // todo: macro
}

// not clear src
static void	transfer_deque_node_all(t_deque *dst, t_deque *src)
{
	t_deque_node	*pop_node;

	while (!deque_is_empty(src))
	{
		pop_node = deque_pop_front(src);
		deque_add_back(dst, pop_node);
	}
}

static void	create_matched_tokens_each(t_deque_node *node, \
										t_deque *matched_tokens)
{
	t_token	*token;
	t_deque	*tmp_matched_tokens;

	token = (t_token *)node->content;
	if (token->quote != QUOTE_NONE)
		deque_add_back(matched_tokens, node);
	else if (!is_wildcard_in_token(token->str))
		deque_add_back(matched_tokens, node);
	else
	{
		tmp_matched_tokens = get_pattern_matched_filenames(token->str);
		if (!tmp_matched_tokens) // todo: error need return..?
			return ;
		if (deque_is_empty(tmp_matched_tokens))
			deque_add_back(matched_tokens, node);
		else
		{
			transfer_deque_node_all(matched_tokens, tmp_matched_tokens);
			deque_clear_node(&node, del_token);
		}
		deque_clear_all(&tmp_matched_tokens, del_token); // only tmp's head
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
	// debug_token_dq(matched_tokens, __func__);
}
