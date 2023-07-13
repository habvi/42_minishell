#include "minishell.h"
#include "ms_tokenize.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_string.h"

void	skip_token_delimiter(char **head)
{
	while (is_whitespace(**head))
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
