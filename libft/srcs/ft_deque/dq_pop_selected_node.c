#include "ft_deque.h"

static void	pop_target_node(t_deque *deque, t_deque_node *node)
{
	(void)deque;
	(void)node;
}
void	deque_pop_selected_node(t_deque *deque, t_deque_node *target_node)
{
	t_deque_node	*node;

	if (!deque || !target_node)
		return ;
	node = deque->node;
	while (node)
	{
		if (node == target_node)
		{
			pop_target_node(deque, target_node);
			return ;
		}
		node = node->next;
	}
}
