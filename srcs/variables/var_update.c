#include "minishell.h"
#include "ms_var.h"

// todo: naming
void	var_update_key_info_pair_and_add(t_var *var, \
											const char *key, \
											const char *value, \
											t_var_attr attr)
{
	t_var_info	*var_info;
	char		*dup_value;

	dup_value = x_ft_strdup(value);
	var_info = var_create_var_info_for_set(var, key, dup_value, attr);
	var->add(var, key, var_info);
	del_var_info((void **)&var_info);
}
