#include "ft_deque.h"

static bool	is_head_node(const t_deque *deque, const t_deque_node *node)
{
	return (deque->node == node);
}

static bool	is_tail_node(const t_deque *deque, const t_deque_node *node)
{
	return (deque->node->prev == node);
}

static void	pop_target_node(t_deque *deque, t_deque_node *node)
{
	t_deque_node	*left_node;
	t_deque_node	*right_node;

	if (deque->size == 1)
	{
		deque_pop_last_node(deque);
		return ;
	}
	if (is_head_node(deque, node))
		deque_pop_front(deque);
	else if (is_tail_node(deque, node))
		deque_pop_back(deque);
	else
	{
		left_node = node->prev;
		right_node = node->next;
		deque_set_next(node, NULL);
		deque_set_prev(node, NULL);
		deque_set_next(left_node, right_node);
		deque_set_prev(right_node, left_node);
		deque->size--;
	}
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
