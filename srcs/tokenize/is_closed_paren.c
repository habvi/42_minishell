#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

static bool	is_valid_paren_pair(const t_token_kind kind, \
										size_t *left, \
										size_t *right)
{
	if (kind == TOKEN_KIND_PAREN_LEFT)
		(*left)++;
	else if (kind == TOKEN_KIND_PAREN_RIGHT)
		(*right)++;
	return (*left >= *right);
}

static bool	is_exceed_limit_depth(const size_t left)
{
	return (left > (size_t)LIMIT_DEPTH);
}

static bool	is_valid_paren_each(const t_token *token, \
								size_t *left, \
								size_t *right)
{
	if (!is_valid_paren_pair(token->kind, left, right))
	{
		puterr_msg_quoted_arg(ERROR_MSG_SYNTAX, token->str);
		return (false);
	}
	if (is_exceed_limit_depth(*left))
	{
		puterr_msg_quoted_arg(ERROR_MSG_SYNTAX, token->str);
		return (false);
	}
	return (true);
}

// if error, status set tokanize().
bool	is_valid_paren_all(t_deque_node *node)
{
	size_t	left;
	size_t	right;
	t_token	*token;

	left = 0;
	right = 0;
	while (node)
	{
		token = (t_token *)node->content;
		if (!is_token_str_paren(token->str))
		{
			node = node->next;
			continue ;
		}
		if (!is_valid_paren_each(token, &left, &right))
			return (false);
		node = node->next;
	}
	if (left != right)
	{
		puterr_msg_quoted_arg(ERROR_MSG_SYNTAX, SYNTAX_DEFAULT_ARG);
		return (false);
	}
	return (true);
}
