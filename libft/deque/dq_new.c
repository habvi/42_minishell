#include "deque.h"
#include <stdlib.h> // malloc

t_deque	*deque_new(void)
{
	t_deque	*deque;

	deque = (t_deque *)malloc(sizeof(t_deque));
	if (!deque)
		return (NULL);
	deque->node = NULL;
	deque->size = 0;
	return (deque);
}
