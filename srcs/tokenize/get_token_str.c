#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_ascii.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

void	skip_token_delimiter(char **head)
{
	while (ft_is_whitespace(**head))
		(*head)++;
}

char	*get_token_str(char *head, char **end)
{
	char	*tail;
	char	*token_str;

	skip_token_delimiter(&head);
	if (!*head)
		return (NULL);
	tail = get_token_tail(head);
	token_str = ft_strndup(head, tail - head);
	if (!token_str)
		ft_abort();
	*end = tail;
	return (token_str);
}

char	*get_head_token_str(const t_deque *command)
{
	t_token	*token;

	if (!command)
		return (NULL);
	if (deque_is_empty(command))
		return (NULL);
	token = (t_token *)command->node->content;
	return (token->str);
}
