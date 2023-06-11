#include <stdio.h>
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_dprintf.h"

// hash table:{
//              [key1, value1],
//              [key2, value2],
//               ...
//              }

static void	print_table_elem(t_deque *deque, void (*display)(void *))
{
	t_deque_node	*node;

	node = deque->node;
	while (node)
	{
		ft_dprintf(STDERR_FILENO, "           ");
		display(node->content);
		node = node->next;
		if (node)
			ft_dprintf(STDERR_FILENO, ",");
		ft_dprintf(STDERR_FILENO, "\n");
	}
}

void	display_hash_table(t_hash *hash, void (*display)(void *))
{
	size_t	idx;

	ft_dprintf(STDERR_FILENO, "hash table:{\n");
	idx = 0;
	while (hash && idx < hash->table_size)
	{
		if (hash->table[idx])
			print_table_elem(hash->table[idx], display);
		idx++;
	}
	ft_dprintf(STDERR_FILENO, "           }\n\n");
}
