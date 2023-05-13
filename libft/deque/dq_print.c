#include "deque.h"

void	deque_print(t_deque *deque)
{
	t_deque_node	*node;

	if (deque_is_empty(deque))
	{
		printf("deque is empty!\n");
		printf("---------------------\n");
		return ;
	}
	printf("cotent: ");
	node = deque->node;
	while (node)
	{
		printf("[%s]", node->content);
		node = node->next;
	}
	printf("\nsize  : %zu\n", deque->size);
	printf("---------------------\n");
}

void	debug_deque_print(t_deque *deque, const char *func_name)
{
	t_deque_node	*node;

	printf(">>> %s\n", func_name);
	if (deque_is_empty(deque))
	{
		printf("deque is empty!\n");
		printf("---------------------\n");
		return ;
	}
	printf("cotent: ");
	node = deque->node;
	while (node)
	{
		printf("[%s]", node->content);
		node = node->next;
	}
	printf("\nsize  : %zu\n", deque->size);
	printf("---------------------\n");
}
