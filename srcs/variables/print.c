#include "minishell.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"

static void	env_print_elem(t_deque *deque)
{
	t_deque_node	*node;
	t_elem			*elem;
	t_var_info		*var_info;
	char			*key;
	char			*value;

	if (!deque)
		return ;
	node = deque->node;
	while (node)
	{
		elem = (t_elem *)node->content;
		var_info = (t_var_info *)elem->value;
		key = elem->key;
		value = var_info->value;
		if (value)
			ft_dprintf(STDOUT_FILENO, "%s=%s\n", key, value);
		node = node->next;
	}
}

// print key-value-pairs to stdout
//   except only key
//   `key=value\n`
void	env_print(t_var *var)
{
	size_t	idx;

	idx = 0;
	while (idx < var->hash->table_size)
	{
		if (var->hash->table[idx] && var->hash->table[idx]->size)
			env_print_elem(var->hash->table[idx]);
		idx++;
	}
}
