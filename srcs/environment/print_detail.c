#include "minishell.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"
#include "ft_sys.h"

static void	set_elem_pointer(t_elem **elems, t_deque **table, const size_t size)
{
	size_t			elem_i;
	size_t			table_i;
	t_deque_node	*node;

	elem_i = 0;
	table_i = 0;
	while (table_i < size)
	{
		if (!table[table_i])
		{
			table_i++;
			continue ;
		}
		node = table[table_i]->node;
		while (node)
		{
			elems[elem_i] = (t_elem *)node->content;
			elem_i++;
			node = node->next;
		}
		table_i++;
	}
}

// print key-value-pairs to stdout
//   include only key
//   `declare -x key="value\n`
int	env_print_detail(t_env *env)
{
	t_elem	**elems;

	elems = (t_elem **)x_malloc(sizeof(t_elem *) * env->hash->key_count);
	if (!elems)
		return (PROCESS_ERROR);
	set_elem_pointer(elems, env->hash->table, env->hash->table_size);
	// sort
	// print
	// free elems
	return (SUCCESS);
}
