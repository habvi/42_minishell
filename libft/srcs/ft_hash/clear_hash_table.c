#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

void	clear_hash_elem(t_elem **elem, void (*del_value)(void *))
{
	if (!elem || !*elem)
		return ;
	ft_free((*elem)->key);
	del_value((*elem)->content);
	(*elem)->content = NULL;
	ft_free(*elem);
}

// todo: use func pointer?
void	tmp_deque_clear_node(t_deque_node **node, void (*del_value)(void *))
{
	t_elem	*elem;

	if (!*node)
		return ;
	elem = (*node)->content;
	ft_free(elem->key);
	del_value(elem->content);
	elem->content = NULL;
	ft_free(elem);
	(*node)->next = NULL;
	(*node)->prev = NULL;
	ft_free(*node);
}

// todo: use func pointer?
static void	tmp_deque_clear_all(t_deque **deque, void (*del_value)(void *))
{
	t_deque_node	*node;
	t_deque_node	*tmp;

	if (deque_is_empty(*deque))
	{
		ft_free(*deque);
		return ;
	}
	node = (*deque)->node;
	while (node)
	{
		tmp = node;
		node = node->next;
		tmp_deque_clear_node(&tmp, del_value);
	}
	ft_free(*deque);
}

void	clear_hash_table(t_hash **hash)
{
	size_t	idx;

	if (!hash || !*hash)
		return ;
	idx = 0;
	while (idx < (*hash)->table_size)
	{
		if ((*hash)->table[idx])
		{
			// deque_clear_all(&(*hash)->table[idx]); // TODO: clear_hash_elem
			tmp_deque_clear_all(&(*hash)->table[idx], (*hash)->del_value);
		}
		idx++;
	}
	free((*hash)->table);
	(*hash)->table = NULL;
	ft_free(*hash);
}
