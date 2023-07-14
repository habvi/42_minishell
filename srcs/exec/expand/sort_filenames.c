#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_string.h"

static bool	is_left_greater_in_ascii(const t_deque_node *left, \
										const t_deque_node *right)
{
	t_token	*left_token;
	t_token	*right_token;

	left_token = (t_token *)left->content;
	right_token = (t_token *)right->content;
	return (left != right && ft_strcmp(left_token->str, right_token->str) > 0);
}

static void	swap_tokens(t_deque_node *left, t_deque_node *right)
{
	void	*tmp;

	tmp = left->content;
	left->content = right->content;
	right->content = tmp;
}

void	sort_filenames(t_deque *tokens)
{
	t_deque_node	*left;
	t_deque_node	*right;

	if (!tokens || deque_is_empty(tokens))
		return ;
	left = tokens->node;
	while (left)
	{
		right = left;
		while (right)
		{
			if (is_left_greater_in_ascii(left, right))
				swap_tokens(left, right);
			right = right->next;
		}
		left = left->next;
	}
}
