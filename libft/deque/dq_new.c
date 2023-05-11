#include "deque.h"
#include "error.h"
#include <stdlib.h> // malloc

t_deque	*deque_new(int num, t_error *error)
{
	t_deque	*node;

	node = (t_deque *)malloc(sizeof(t_deque));
	if (node == NULL)
	{
		*error = ERROR_MALLOC;
		return (NULL);
	}
	node->num = num;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
