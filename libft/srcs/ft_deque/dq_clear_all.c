#include "ft_deque.h"
#include "ft_mem.h"

void	deque_clear_all(t_deque **deque, void (*del)(void *))
{
	t_deque_node	*node;
	t_deque_node	*tmp;

	if (deque_is_empty(*deque))
	{
		ft_free(deque);
		return ;
	}
	node = (*deque)->node;
	while (node)
	{
		tmp = node;
		node = node->next;
		deque_clear_node(&tmp, del);
	}
	ft_free(deque);
}
