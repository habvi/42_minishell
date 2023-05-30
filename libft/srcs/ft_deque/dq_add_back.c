#include "ft_deque.h"

void	deque_add_back(t_deque *deque, t_deque_node *new_node)
{
	t_deque_node	*tail;

	if (!new_node)
		return ;
	if (deque_is_empty(deque))
	{
		deque_add_first_node(deque, new_node);
		return ;
	}
	tail = deque->node->prev;
	deque_set_next(tail, new_node);
	deque_set_prev(new_node, tail);
	deque_set_prev(deque->node, new_node);
	deque->size += 1;
}
