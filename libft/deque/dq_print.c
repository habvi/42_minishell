#include "deque.h"

void	deque_print(t_deque *deque)
{
	t_deque	*node;

	if (deque_is_empty(deque))
	{
		printf("deque is empty!\n");
		printf("---------------------\n");
		return ;
	}
	node = deque->next;
	while (node)
	{
		printf("[%p] num: %d\n", node, node->num);
		node = node->next;
	}
	printf("---------------------\n");
}
