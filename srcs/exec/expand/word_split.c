#include "minishell.h"
#include "ms_tokenize.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

static char	*get_split_tail(char *head)
{
	char	*tail;

	tail = head;
	while (*tail && !is_whitespace(*tail))
		tail++;
	return (tail);
}

static char	*get_split_str(char *head, char **end)
{
	char	*tail;
	char	*split_str;

	skip_token_delimiter(&head);
	if (!*head)
		return (NULL);
	tail = get_split_tail(head);
	split_str = ft_strndup(head, tail - head);
	if (!split_str)
		ft_abort();
	*end = tail;
	return (split_str);
}

// [   aaa  bbb ccc] -> [aaa],[bbb],[ccc]
// [key1  key2=a  b   c] -> [key1],[key2=a],[b],[c]
void	word_split_and_add(char *token_str, t_deque *expanded)
{
	char			*split_str;
	char			*end;
	t_deque_node	*node;

	while (*token_str)
	{
		split_str = get_split_str(token_str, &end);
		if (!split_str)
			break ;
		node = create_token_node(split_str, *end);
		deque_add_back(expanded, node);
		token_str = end;
	}
}
