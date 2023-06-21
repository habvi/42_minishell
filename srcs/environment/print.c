#include "minishell.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"

static void	env_print_elem(t_deque *deque)
{
	t_deque_node	*node;
	t_elem			*elem;
	char			*key;
	char			*value;

	if (!deque)
		return ;
	node = deque->node;
	while (node)
	{
		elem = (t_elem *)node->content;
		key = elem->key;
		value = elem->value;
		if (value)
			ft_dprintf(STDOUT_FILENO, "%s=%s\n", key, value);
		node = node->next;
	}
}

// print key-value-pairs to stdout
//   except only key
//   `key=value\n`
void	env_print(t_env *env)
{
	size_t	idx;

	idx = 0;
	while (idx < env->hash->table_size)
	{
		if (env->hash->table[idx] && env->hash->table[idx]->size)
			env_print_elem(env->hash->table[idx]);
		idx++;
	}
}

// print key-value-pairs to stdout
//   include only key
//   `declare -x key="value\n`
void	env_print_detail(t_env *env)
{
	(void)env;
}
