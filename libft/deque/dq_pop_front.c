#include "deque.h"

t_deque	*deque_pop_front(t_deque *deque)
{
	t_deque	*pop_node;
	t_deque	*new_front;

	if (deque_is_empty(deque))
		return (NULL);
	pop_node = deque->next;
	new_front = pop_node->next;
	if (new_front == NULL)
		deque_init(deque, 0, deque);
	else
	{
		deque_set_next(deque, new_front);
		deque_set_prev(new_front, deque);
	}
	deque_init(pop_node, pop_node->num, NULL);
	return (pop_node);
}
