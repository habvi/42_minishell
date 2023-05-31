#include "ft_deque.h"

void	deque_add_first_node(t_deque *deque, t_deque_node *new_node)
{
	deque->node = new_node;
	deque_set_prev(deque->node, new_node);
	deque->size += 1;
}

void	deque_add_front(t_deque *deque, t_deque_node *new_node)
{
	t_deque_node	*head;
	t_deque_node	*tail;

	if (!new_node)
		return ;
	if (deque_is_empty(deque))
	{
		deque_add_first_node(deque, new_node);
		return ;
	}
	head = deque->node;
	tail = deque->node->prev;
	deque_set_prev(head, new_node);
	deque_set_next(new_node, head);
	deque_set_prev(new_node, tail);
	deque->node = new_node;
	deque->size += 1;
}
