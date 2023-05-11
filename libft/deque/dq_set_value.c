#include "deque.h"

void	deque_set_next(t_deque *deque, t_deque *next)
{
	deque->next = next;
}

void	deque_set_prev(t_deque *deque, t_deque *prev)
{
	deque->prev = prev;
}
