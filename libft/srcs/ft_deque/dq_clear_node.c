#include <stdlib.h>
#include "ft_deque.h"

//void	deque_clear_node(t_deque_node **node)
//{
//	if (!*node)
//		return ;
//	free((*node)->content);
//	(*node)->content = NULL;
//	(*node)->next = NULL;
//	(*node)->prev = NULL;
//	free(*node);
//	*node = NULL;
//}

void	deque_clear_node(t_deque_node **node, void (*del)(void *))
{
	if (!*node)
		return ;
	del((*node)->content);
	(*node)->content = NULL;
	(*node)->next = NULL;
	(*node)->prev = NULL;
	free(*node);
	*node = NULL;
}
