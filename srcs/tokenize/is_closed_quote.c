#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_string.h"

static bool	is_closed_quote_each_token(char *token_str)
{
	const size_t	len = ft_strlen(token_str);
	const char		head = *token_str;
	const char		tail = token_str[len];

	if (is_token_str_quote(token_str))
	{
		if (head != tail)
			return (false);
	}
	return (true);
}

// if error, status set tokanize().
bool	is_closed_quote_all(t_deque_node *node)
{
	t_token	*token;

	while (node)
	{
		token = (t_token *)node->content;
		if (!is_closed_quote_each_token(token->str))
		{
			ft_dprintf(STDERR_FILENO, "%s\n", ERROR_MSG_SYNTAX); // todo: print
			return (false);
		}
		node = node->next;
	}
	return (true);
}
