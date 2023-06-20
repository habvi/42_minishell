#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

void	hs_clear_elem(t_elem **elem, void (*del_value)(void *))
{
	if (!elem || !*elem)
		return ;
	ft_free((*elem)->key);
	del_value((*elem)->value);
	(*elem)->value = NULL;
	ft_free(*elem);
}

void	hs_clear_deque_node(t_deque_node **node, void (*del_value)(void *))
{
	t_elem	*elem;

	if (!*node)
		return ;
	elem = (t_elem *)(*node)->content;
	hs_clear_elem(&elem, del_value);
	(*node)->next = NULL;
	(*node)->prev = NULL;
	ft_free(*node);
}

static void	hash_clear_deque_all(t_deque **deque, void (*del_value)(void *))
{
	t_deque_node	*node;
	t_deque_node	*tmp;

	if (deque_is_empty(*deque))
	{
		ft_free(*deque);
		*deque = NULL;
		return ;
	}
	node = (*deque)->node;
	while (node)
	{
		tmp = node;
		node = node->next;
		hs_clear_deque_node(&tmp, del_value);
	}
	ft_free(*deque);
	*deque = NULL;
}

void	hs_clear_table(t_hash **hash)
{
	size_t	idx;

	if (!hash || !*hash)
		return ;
	idx = 0;
	while (idx < (*hash)->table_size)
	{
		if ((*hash)->table[idx])
			hash_clear_deque_all(&(*hash)->table[idx], (*hash)->del_value);
		idx++;
	}
	free((*hash)->table);
	(*hash)->table = NULL;
	ft_free(*hash);
}
