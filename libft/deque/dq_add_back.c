#include "deque.h"

void	deque_add_back(t_deque *deque, t_deque *new_node)
{
	t_deque	*tail;

	tail = deque->prev;
	deque_set_next(tail, new_node);
	deque_set_prev(new_node, tail);
	deque_set_prev(deque, new_node);
}
