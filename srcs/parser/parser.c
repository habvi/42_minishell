#include "parser.h"
#include "deque.h"
#include "libft.h"
#include "tokenize.h"

// todo: into libft ?
bool	is_equal_strings(const char *str1, const char *str2)
{
	size_t	str1_len;
	size_t	str2_len;

	if (!str1 && !str2)
		return (true);
	if (!str1 || !str2)
		return (false);
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	if (str1_len != str2_len)
		return (false);
	if (ft_strncmp(str1, str2, str1_len) == 0)
		return (true);
	return (false);
}

// dq_token->node != NULL ??
bool	is_pipe_token(t_deque *dq_token)
{
	const t_token	*token = dq_token->node->content;

	return (is_equal_strings(token->str, "|"));
}

// dq_node != NULL ??
// append dq node until pipe
t_ast	*parse_command_leaf(t_deque *dq_token)
{
	t_deque			*cmd_head;
	t_deque_node	*cmd_node;
	t_ast			*cmd_line;

	cmd_head = deque_new();
	if (!cmd_head)
		return (NULL);
	while (!is_pipe_token(dq_token))
	{
		cmd_node = deque_pop_front(dq_token);
		deque_add_back(cmd_head, cmd_node);
	}
	cmd_line = new_command_leaf(cmd_head);
	if (!cmd_line) // if handle error
		return (NULL);
	return (cmd_line);
}

void	pop_pipe_and_clear(t_deque *dq_token)
{
	t_deque_node	*pop;

	pop = deque_pop_front(dq_token);
	deque_clear_node(&pop);
}

// a b c | d e f | h i j
// a -> b -> c -> | -> ..
// [cmd1] -> | -> [cmd2] ->
t_ast	*parser(t_deque *dq_token)
{
	t_ast			*left;
	t_ast			*right;

	left = parse_command_leaf(dq_token);
	while (dq_token->size && is_pipe_token(dq_token))
	{
		pop_pipe_and_clear(dq_token);
		right = parse_command_leaf(dq_token);
		if (!right)
			exit (EXIT_FAILURE);
		left = new_node(NODE_PIPE, left, right);
		if (!left)
			exit (EXIT_FAILURE);
	}
	return (left);
}
