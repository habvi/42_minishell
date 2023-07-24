#include "ft_deque.h"
#include "ft_mem.h"

void	deque_clear_node(t_deque_node **node, void (*del)(void *))
{
	if (!*node)
		return ;
	del((*node)->content);
	(*node)->content = NULL;
	(*node)->next = NULL;
	(*node)->prev = NULL;
	ft_free((void **)node);
}
