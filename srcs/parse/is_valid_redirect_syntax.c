#include "ms_tokenize.h"
#include "ft_deque.h"

static bool	is_valid_redirect_syntax_each(const t_token *cur_token, \
											const t_token *next_token)
{
	if (!is_token_kind_redirection(cur_token->kind))
		return (true);
	if (next_token && next_token->kind == TOKEN_KIND_WORD)
		return (true);
	return (false);
}

static t_token	*get_next_token(const t_deque_node *cur_node)
{
	if (!cur_node->next)
		return (NULL);
	return ((t_token *)cur_node->next->content);
}

// format: op word, word needed
bool	is_valid_redirect_syntax_all(t_deque_node **node)
{
	t_token	*cur_token;
	t_token	*next_token;

	while (*node)
	{
		cur_token = (t_token *)(*node)->content;
		next_token = get_next_token(*node);
		if (!is_valid_redirect_syntax_each(cur_token, next_token))
		{
			*node = (*node)->next;
			return (false);
		}
		*node = (*node)->next;
	}
	return (true);
}
