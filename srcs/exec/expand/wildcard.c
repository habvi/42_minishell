#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_string.h"

static bool	is_wildcard_in_token(const char *str)
{
	return (ft_strchr_bool(str, WILDCARD));
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

// tmp_matched_tokens != NULL
static t_result	create_matched_tokens_each(t_deque_node *node, \
											t_deque *matched_tokens)
{
	t_token		*token;
	t_deque		*tmp_matched_tokens;
	t_result	result;

	token = (t_token *)node->content;
	if (token->quote == QUOTE_NONE && is_wildcard_in_token(token->str))
	{
		tmp_matched_tokens = get_pattern_matched_filenames(token, &result);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (!deque_is_empty(tmp_matched_tokens))
		{
			transfer_deque_node_all(matched_tokens, tmp_matched_tokens);
			deque_clear_node(&node, del_token);
		}
		deque_add_back(matched_tokens, node);
		deque_clear_all(&tmp_matched_tokens, del_token); // remain only head
		return (SUCCESS);
	}
	deque_add_back(matched_tokens, node);
	return (SUCCESS);
}

static t_deque	*create_matched_tokens_all(t_deque *tokens, t_result *result)
{
	t_deque			*matched_tokens;
	t_deque_node	*node;

	matched_tokens = deque_new();
	if (!matched_tokens)
		ft_abort();
	while (!deque_is_empty(tokens))
	{
		node = deque_pop_front(tokens);
		*result = create_matched_tokens_each(node, matched_tokens);
		if (*result == PROCESS_ERROR)
			return (NULL);
	}
	return (matched_tokens);
}

t_result	expand_wildcard(t_deque **tokens)
{
	t_result	result;
	t_deque		*matched_tokens;

	if (!*tokens)
		return (SUCCESS);
	result = SUCCESS;
	matched_tokens = create_matched_tokens_all(*tokens, &result);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	deque_clear_all(tokens, del_token);
	*tokens = matched_tokens;
	// debug_token_dq(matched_tokens, __func__);
	return (SUCCESS);
}
