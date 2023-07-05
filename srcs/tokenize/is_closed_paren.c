#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

static bool	is_valid_paren_each_token(const t_token_kind kind, \
										size_t *left, \
										size_t *right)
{
	if (kind == TOKEN_KIND_PAREN_LEFT)
		(*left)++;
	else if (kind == TOKEN_KIND_PAREN_RIGHT)
		(*right)++;
	return (*left >= *right);
}

static bool	print_error_msg_return_false(void)
{
	ft_dprintf(STDERR_FILENO, "%s\n", "tokenize paren error"); // todo: print
	return (false);
}

// if error, status set tokanize().
bool	is_valid_paren_pair_all(t_deque_node *node)
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
		if (!is_valid_paren_each_token(token->kind, &left, &right))
			return (print_error_msg_return_false());
		node = node->next;
	}
	if (left != right)
		return (print_error_msg_return_false());
	return (true);
}
