#include "ft_deque.h"

bool	deque_is_empty(const t_deque *deque)
{
	if (deque->size == 0)
		return (true);
	return (false);
}
