#include "minishell.h"
#include "ms_var.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_sys.h"

static void	set_var_variable_elem(t_deque_node *node, \
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
		set_var_variable_elem(table[i]->node, elems, &j, attr);
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

// stdout
// declare -x KEY="VALUE"
// declare -x KEY"
static void	print_elems(t_elem **elems, bool is_display_attr)
{
	size_t		i;
	t_var_info	*var_info;
	char		*attr;
	char		*quote;

	i = 0;
	quote = "";
	while (elems[i])
	{
		var_info = (t_var_info *)elems[i]->value;
		attr = get_print_attr(var_info->attr);
		if (is_display_attr)
		{
			ft_dprintf(STDOUT_FILENO, "%s %s ", DECLARE, attr);
			quote = VAR_PRINT_QUOTE;
		}
		ft_dprintf(STDOUT_FILENO, "%s", elems[i]->key);
		if (var_info->value)
			ft_dprintf(STDOUT_FILENO, "=%s%s%s", quote, var_info->value, quote);
		ft_dprintf(STDOUT_FILENO, "\n");
		i++;
	}
}

// print key-value-pairs to stdout
//   include only key
//   `declare -x key="value\n`
void	var_print_detail(t_var *var, t_var_attr attr, bool is_display_attr)
{
	t_elem	**elems;

	elems = (t_elem **)x_malloc(sizeof(t_elem *) * (var->hash->key_count + 1));
	if (!elems)
		ft_abort();
	set_elem_pointer(elems, var->hash->table, var->hash->table_size, attr);
	var_sort_elems_by_key(elems);
	print_elems(elems, is_display_attr);
	ft_free(&elems);
}
