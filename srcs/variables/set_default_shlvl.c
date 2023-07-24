#include <limits.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_hash.h"
#include "ft_mem.h"

static int	get_new_shlvl_by_positive_num(long parent_lvl)
{
	if (parent_lvl < (long)SHLVL_LIMIT)
		return ((int)parent_lvl + 1);
	if (parent_lvl < (long)INT_MAX)
	{
		ft_dprintf(2, \
			"%s: %s: shell level (%d) too high, resetting to %d\n", \
			SHELL_NAME, ERROR_TYPE_WARNING, parent_lvl + 1, 1);
		return (SHLVL_RESET);
	}
	return (SHLVL_ZERO);
}

static int	get_new_shlvl_value(t_var *var)
{
	char	*parent_lvl_str;
	bool	is_legal_num;
	long	parent_lvl_num;

	parent_lvl_str = var->get_value(var, KEY_SHLVL);
	is_legal_num = str_to_legal_number(parent_lvl_str, &parent_lvl_num);
	ft_free((void **)&parent_lvl_str);
	if (!is_legal_num)
		return (SHLVL_RESET);
	if (parent_lvl_num < 0)
		parent_lvl_num -= LONG_MIN;
	return (get_new_shlvl_by_positive_num(parent_lvl_num));
}

static char	*get_new_shlvl_str(t_var *var)
{
	int		new_lvl_num;
	char	*new_lvl_str;

	new_lvl_num = get_new_shlvl_value(var);
	new_lvl_str = x_ft_itoa(new_lvl_num);
	return (new_lvl_str);
}

void	set_default_shlvl(t_var *var)
{
	char	*new_lvl_str;

	new_lvl_str = get_new_shlvl_str(var);
	var->add(var, KEY_SHLVL, new_lvl_str, VAR_ENV);
	ft_free((void **)&new_lvl_str);
}
