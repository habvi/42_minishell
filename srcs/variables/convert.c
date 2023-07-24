#include "minishell.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_sys.h"

static size_t	count_key_value_pair(t_deque_node *node)
{
	size_t		size;
	t_elem		*elem;
	t_var_info	*var_info;

	size = 0;
	while (node)
	{
		elem = (t_elem *)node->content;
		var_info = (t_var_info *)elem->value;
		if (elem->key && var_info->value)
			size++;
		node = node->next;
	}
	return (size);
}

static size_t	count_envp_size(t_hash *hash)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (i < hash->table_size)
	{
		if (hash->table[i] && hash->table[i]->size)
			size += count_key_value_pair(hash->table[i]->node);
		i++;
	}
	return (size);
}

static char	*create_key_value_pair(const char *key, const char *value)
{
	char	*join_str;
	char	*tmp;

	join_str = x_ft_strjoin(key, ASSIGNMENT_STR);
	tmp = join_str;
	join_str = x_ft_strjoin(tmp, value);
	ft_free((void **)&tmp);
	return (join_str);
}

static void	convert_elem_to_env(char **envp, t_deque *deque)
{
	t_deque_node	*node;
	t_elem			*elem;
	t_var_info		*var_info;
	static size_t	i = 0;

	if (!deque)
		return ;
	node = deque->node;
	while (node)
	{
		elem = (t_elem *)node->content;
		var_info = (t_var_info *)elem->value;
		if (elem->key && var_info->value)
		{
			envp[i] = create_key_value_pair(elem->key, var_info->value);
			i++;
		}
		node = node->next;
	}
}

char	**var_convert_to_envp(t_var *var)
{
	char			**envp;
	const size_t	size = count_envp_size(var->hash);
	size_t			i;

	envp = (char **)x_malloc(sizeof(char *) * (size + 1));
	if (!envp)
		ft_abort();
	i = 0;
	while (i < var->hash->table_size)
	{
		if (var->hash->table[i] && var->hash->table[i]->size)
			convert_elem_to_env(envp, var->hash->table[i]);
		i++;
	}
	envp[size] = NULL;
	return (envp);
}
