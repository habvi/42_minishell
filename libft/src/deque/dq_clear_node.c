#include <stdlib.h>
#include "deque.h"

void	deque_clear_node(t_deque_node **node)
{
	if (!*node)
		return ;
	free((*node)->content);
	(*node)->content = NULL;
	(*node)->next = NULL;
	(*node)->prev = NULL;
	free(*node);
	*node = NULL;
}
