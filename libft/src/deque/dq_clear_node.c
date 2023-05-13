#include <stdlib.h>
#include "deque.h"

void	deque_clear_node(t_deque_node **node)
{
	char	*content;

	content = (*node)->content;
	free(content);
	content = NULL;
	(*node)->next = NULL;
	(*node)->prev = NULL;
	free(*node);
	*node = NULL;
}
