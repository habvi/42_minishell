#include "deque.h"

void	deque_add_front(t_deque *deque, t_deque *new_node)
{
	t_deque	*head;

	head = deque->next;
	if (!deque_is_empty(deque))
		deque_set_next(new_node, head);
	deque_set_prev(head, new_node);
	deque_set_next(deque, new_node);
	deque_set_prev(new_node, deque);
}
