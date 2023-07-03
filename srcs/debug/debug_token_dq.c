#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

void	debug_token_dq(t_deque *deque, const char *str)
{
	t_deque_node	*node;
	t_token			*token;

	ft_dprintf(STDERR_FILENO, "deque_print(%d) %s :", deque->size, str);
	if (deque_is_empty(deque))
		return ;
	node = deque->node;
	while (node)
	{
		token = (t_token *)node->content;
		ft_dprintf(STDERR_FILENO, "[%s]", token->str);
		node = node->next;
		if (node)
		{
			if (token->concat_next)
				ft_dprintf(STDERR_FILENO, "=");
			else
				ft_dprintf(STDERR_FILENO, ", ");
		}
	}
	ft_dprintf(STDERR_FILENO, "\n");
}
