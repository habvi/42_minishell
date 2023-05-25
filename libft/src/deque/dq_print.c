#include <stdio.h>
#include "deque.h"
#include "ft_dprintf.h"

void	deque_print(t_deque *deque)
{
	t_deque_node	*node;

	if (deque_is_empty(deque))
	{
		ft_dprintf(STDERR_FILENO, "deque is empty!\n");
		ft_dprintf(STDERR_FILENO, "---------------------\n");
		return ;
	}
	ft_dprintf(STDERR_FILENO, "cotent: ");
	node = deque->node;
	while (node)
	{
		ft_dprintf(STDERR_FILENO, "[%s]", (char *)node->content);
		node = node->next;
	}
	ft_dprintf(STDERR_FILENO, "\nsize  : %zu\n", deque->size);
	ft_dprintf(STDERR_FILENO, "---------------------\n");
}

void	debug_deque_print(t_deque *deque, const char *func_name)
{
	ft_dprintf(STDERR_FILENO, ">>> %s\n", func_name);
	deque_print(deque);
}
