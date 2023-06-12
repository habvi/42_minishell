#include <stdlib.h>
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

void	del(void *content)
{
	free(content);
}

void	clear_hash_elem(t_elem **elem, void (*del)(void *))
{
	if (!elem || !*elem)
		return ;
	ft_free((*elem)->key);
	del((*elem)->content);
	(*elem)->content = NULL;
	ft_free(*elem);
}

// todo: use func pointer?
static void	tmp_deque_clear_node(t_deque_node **node)
{
	t_elem	*elem;

	if (!*node)
		return ;
	elem = (*node)->content;
	ft_free(elem->key);
	free(elem->content);
	elem->content = NULL;
	ft_free(elem);
	(*node)->next = NULL;
	(*node)->prev = NULL;
	ft_free(*node);
}

// todo: use func pointer?
static void	tmp_deque_clear_all(t_deque **deque)
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
		tmp_deque_clear_node(&tmp);
	}
	ft_free(*deque);
}

// hash->table not use ft_free
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
			tmp_deque_clear_all(&(*hash)->table[idx]);
		}
		idx++;
	}
	free((*hash)->table);
	(*hash)->table = NULL;
	ft_free(*hash);
}
