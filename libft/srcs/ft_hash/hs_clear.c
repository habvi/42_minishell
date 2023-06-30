#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

#include <stdio.h>
void	hs_clear_elem(t_elem **elem, void (*del_hash_value)(void **))
{
	if (!elem || !*elem)
		return ;
	ft_free(&(*elem)->key);
	del_hash_value(&(*elem)->value);
	ft_free(elem);
}

void	hs_clear_deque_node(t_deque_node **node, void (*del_hash_value)(void **))
{
	t_elem	*elem;

	if (!*node)
		return ;
	elem = (t_elem *)(*node)->content;
	hs_clear_elem(&elem, del_hash_value);
	(*node)->next = NULL;
	(*node)->prev = NULL;
	ft_free(node);
}

static void	hash_clear_deque_all(t_deque **deque, void (*del_hash_value)(void **))
{
	t_deque_node	*node;
	t_deque_node	*tmp;

	if (deque_is_empty(*deque))
	{
		ft_free(deque);
		*deque = NULL;
		return ;
	}
	node = (*deque)->node;
	while (node)
	{
		tmp = node;
		node = node->next;
		hs_clear_deque_node(&tmp, del_hash_value);
	}
	ft_free(deque);
	*deque = NULL;
}

void	hs_clear_table(t_deque **table, \
						const size_t size, \
						void (*del_hash_value)(void **))
{
	size_t	idx;

	if (!table || !del_hash_value)
		return ;
	idx = 0;
	while (idx < size)
	{
		if (table[idx])
			hash_clear_deque_all(&table[idx], del_hash_value);
		idx++;
	}
	ft_free(&table);
}

void	hs_clear(t_hash **hash)
{
	if (!hash || !*hash)
		return ;
	hs_clear_table((*hash)->table, (*hash)->table_size, (*hash)->del_hash_value);
	ft_free(hash);
}
