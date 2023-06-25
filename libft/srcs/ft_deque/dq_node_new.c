#include "ft_deque.h"
#include "ft_sys.h"

t_deque_node	*deque_node_new(void *content)
{
	t_deque_node	*node;

	node = (t_deque_node *)x_malloc(sizeof(t_deque_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
