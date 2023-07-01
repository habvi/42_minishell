#include "minishell.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_sys.h"

static void	set_env_variable_elem(t_deque_node *node, \
									t_elem **elems, \
									size_t *j, \
									t_var_attr attr)
{
	t_elem		*elem;
	t_var_info	*var_info;

	while (node)
	{
		elem = (t_elem *)node->content;
		var_info = (t_var_info *)elem->value;
		if (var_info->attr & attr)
		{
			elems[*j] = elem;
			(*j)++;
		}
		node = node->next;
	}
}

static void	set_elem_pointer(t_elem **elems, \
								t_deque **table, \
								const size_t table_size,
								t_var_attr attr)
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
		set_env_variable_elem(table[i]->node, elems, &j, attr);
		i++;
	}
	elems[j] = NULL;
}

static char	*get_print_attr(t_var_attr attr)
{
	if (attr & VAR_ENV)
		return (ATTR_ENV);
	if (attr & VAR_SHELL)
		return (ATTR_SHELL);
	return (ATTR_NONE);
}

// declare -x KEY="VALUE"
// declare -x KEY"
static void	print_elems(t_elem **elems)
{
	size_t		i;
	t_var_info	*var_info;
	char		*attr;

	i = 0;
	while (elems[i])
	{
		var_info = (t_var_info *)elems[i]->value;
		attr = get_print_attr(var_info->attr);
		ft_dprintf(STDOUT_FILENO, "%s %s %s", DECLARE, attr, elems[i]->key);
		if (var_info->value)
			ft_dprintf(STDOUT_FILENO, "=\"%s\"", var_info->value);
		ft_dprintf(STDOUT_FILENO, "\n");
		i++;
	}
}

// print key-value-pairs to stdout
//   include only key
//   `declare -x key="value\n`
void	env_print_detail(t_env *env, t_var_attr attr)
{
	t_elem	**elems;

	elems = (t_elem **)x_malloc(sizeof(t_elem *) * (env->hash->key_count + 1));
	if (!elems)
		ft_abort();
	set_elem_pointer(elems, env->hash->table, env->hash->table_size, attr);
	sort_elems_by_key(elems);
	print_elems(elems);
	ft_free(&elems);
}
