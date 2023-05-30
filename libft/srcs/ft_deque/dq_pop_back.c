#include "ft_deque.h"

t_deque_node	*deque_pop_back(t_deque *deque)
{
	t_deque_node	*pop_node;
	t_deque_node	*new_tail;

	if (deque_is_empty(deque))
		return (NULL);
	if (deque->size == 1)
	{
		pop_node = deque_pop_last_node(deque);
		return (pop_node);
	}
	pop_node = deque->node->prev;
	new_tail = pop_node->prev;
	deque_set_next(new_tail, NULL);
	deque_set_prev(deque->node, new_tail);
	deque_set_prev(pop_node, NULL);
	deque->size -= 1;
	return (pop_node);
}
