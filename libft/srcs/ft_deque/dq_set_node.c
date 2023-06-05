#include "ft_deque.h"

void	deque_set_next(t_deque_node *node, t_deque_node *new_node)
{
	node->next = new_node;
}

void	deque_set_prev(t_deque_node *node, t_deque_node *new_node)
{
	node->prev = new_node;
}
