#include "deque.h"
#include <stdlib.h> // malloc

t_deque_node    *deque_node_new(void)
{
	t_deque_node    *node;

	node = (t_deque_node *)malloc(sizeof(t_deque_node));
	if (!node)
		return (NULL);
	node->content = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
