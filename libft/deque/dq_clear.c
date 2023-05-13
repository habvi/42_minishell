#include <stdlib.h>
#include "deque.h"

void	deque_clear(t_deque **deque)
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
		free(tmp->content);
		tmp->content = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	free(*deque);
	*deque = NULL;
}
