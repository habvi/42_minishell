#include "deque.h"

t_deque	*deque_pop_back(t_deque *deque)
{
	t_deque	*pop_node;
	t_deque	*new_tail;

	if (deque_is_empty(deque))
		return (NULL);
	pop_node = deque->prev;
	new_tail = pop_node->prev;
	if (new_tail == deque)
		deque_set_next(deque, deque);
	else
		deque_set_next(new_tail, NULL);
	deque_set_prev(deque, new_tail);
	deque_init(pop_node, pop_node->num, NULL);
	return (pop_node);
}
