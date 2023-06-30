#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

static void	set_env_variable_elem(t_deque_node *node, t_elem **elems, size_t *j)
{
	t_elem		*elem;
	t_var_info	*var_info;

	while (node)
	{
		elem = (t_elem *)node->content;
		var_info = (t_var_info *)elem->value;
		if (var_info->attr == VAR_ENV)
		{
			elems[*j] = elem;
			(*j)++;
		}
		node = node->next;
	}
}

static void	set_elem_pointer(t_elem **elems, \
								t_deque **table, \
								const size_t table_size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < table_size)
	{
		if (!table[i])
		{
			i++;
			continue ;
		}
		set_env_variable_elem(table[i]->node, elems, &j);
		i++;
	}
	elems[j] = NULL;
}

static void	swap_elems(t_elem **elems, const size_t i, const size_t j)
{
	t_elem	*tmp;

	tmp = elems[i];
	elems[i] = elems[j];
	elems[j] = tmp;
}

// sort to ascending
// i <-> j
static void	sort_elems_by_key(t_elem **elems)
{
	size_t	i;
	size_t	j;
	char	*key_i;
	char	*key_j;

	i = 0;
	while (elems[i])
	{
		j = i;
		while (elems[j])
		{
			key_i = elems[i]->key;
			key_j = elems[j]->key;
			if (i != j && ft_strcmp(key_i, key_j) > 0)
				swap_elems(elems, i, j);
			j++;
		}
		i++;
	}
}

// declare -x KEY="VALUE"
// declare -x KEY"
static void	print_elems(t_elem **elems)
{
	size_t		i;
	t_var_info	*var_info;

	i = 0;
	while (elems[i])
	{
		var_info = (t_var_info *)elems[i]->value;
		if (var_info->value)
			ft_dprintf(STDOUT_FILENO, "%s %s=\"%s\"\n", \
				DECLARE_X, elems[i]->key, var_info->value);
		else
			ft_dprintf(STDOUT_FILENO, "%s %s\n", \
				DECLARE_X, elems[i]->key);
		i++;
	}
}

// print key-value-pairs to stdout
//   include only key
//   `declare -x key="value\n`
void	env_print_detail(t_env *env)
{
	t_elem	**elems;

	elems = (t_elem **)x_malloc(sizeof(t_elem *) * (env->hash->key_count + 1));
	if (!elems)
		ft_abort();
	set_elem_pointer(elems, env->hash->table, env->hash->table_size);
	sort_elems_by_key(elems);
	print_elems(elems);
	ft_free(&elems);
}
