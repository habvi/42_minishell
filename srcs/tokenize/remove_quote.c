#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_mem.h"

// token->str is quoted -> len >= 2
static void	remove_quote_in_token_str_each(t_token *token)
{
	const size_t	len = ft_strlen(token->str);
	char			*quote_removed;

	quote_removed = ft_substr(token->str, 1, len - 2);
	if (!quote_removed)
		ft_abort();
	ft_free(&token->str);
	token->str = quote_removed;
}

void	remove_quote_in_token_str(t_deque *tokens)
{
	t_deque_node	*token_node;
	t_token			*token;

	token_node = tokens->node;
	while (token_node)
	{
		token = (t_token *)token_node->content;
		if (token->quote == QUOTE_NONE)
		{
			token_node = token_node->next;
			continue ;
		}
		remove_quote_in_token_str_each(token);
		token_node = token_node->next;
	}
}
