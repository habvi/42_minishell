#include "deque.h"

bool	deque_is_empty(t_deque *deque)
{
	if (!deque || deque->size == 0)
		return (true);
	return (false);
}
