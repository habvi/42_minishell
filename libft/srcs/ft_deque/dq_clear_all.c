#include <stdlib.h>
#include "ft_deque.h"

void	deque_clear_all(t_deque **deque)
{
	t_deque_node	*node;
	t_deque_node	*tmp;

	if (deque_is_empty(*deque))
	{
		free(*deque);
		return ;
	}
	node = (*deque)->node;
	while (node)
	{
		tmp = node;
		node = node->next;
		deque_clear_node(&tmp);
	}
	free(*deque);
	*deque = NULL;
}
