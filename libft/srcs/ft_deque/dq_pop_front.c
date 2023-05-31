#include "ft_deque.h"

t_deque_node	*deque_pop_last_node(t_deque *deque)
{
	t_deque_node	*pop_node;

	pop_node = deque->node;
	deque_set_prev(pop_node, NULL);
	deque->node = NULL;
	deque->size -= 1;
	return (pop_node);
}

t_deque_node	*deque_pop_front(t_deque *deque)
{
	t_deque_node	*pop_node;
	t_deque_node	*new_front;

	if (deque_is_empty(deque))
		return (NULL);
	if (deque->size == 1)
	{
		pop_node = deque_pop_last_node(deque);
		return (pop_node);
	}
	pop_node = deque->node;
	new_front = pop_node->next;
	deque->node = new_front;
	deque_set_next(pop_node, NULL);
	deque_set_prev(new_front, pop_node->prev);
	deque_set_prev(pop_node, NULL);
	deque->size -= 1;
	return (pop_node);
}
