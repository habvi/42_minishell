#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_string.h"

static bool	is_closed_quote_each_token(char *token_str)
{
	const size_t	len = ft_strlen(token_str);
	const char		head = *token_str;
	char			tail;

	if (!is_token_str_quote(token_str))
		return (true);
	if (len == 1)
		return (false);
	tail = token_str[len - 1];
	if (head != tail)
		return (false);
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
			puterr_msg_quoted_arg(ERROR_MSG_SYNTAX, SYNTAX_DEFAULT_ARG);
			return (false);
		}
		node = node->next;
	}
	return (true);
}
