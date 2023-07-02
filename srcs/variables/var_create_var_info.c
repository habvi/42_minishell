#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"
#include "ft_sys.h"

// todo: check: if key_exist and value=NULL, use key's value
// todo: can be more simple var_add and var_join ? ;maybe...
// todo: func name
static char	*update_value_based_on_key(t_var *var, \
										const char *key, \
										char *value)
{
	if (value)
		return (value);
	if (!var_is_key_exist(var, key))
		return (NULL);
	value = var->get_value(var, key);
	return (value);
}

// all malloc
// key=value -> key, = ,value, attr
t_var_info	*var_create_var_info(const char *value, t_var_attr attr)
{
	t_var_info	*var_info;
	char		*dup_value;

	var_info = (t_var_info *)x_malloc(sizeof(t_var_info));
	if (!var_info)
		ft_abort();
	if (value)
		dup_value = x_ft_strdup(value);
	else
		dup_value = NULL;
	var_info->value = dup_value;
	var_info->attr = attr;
	return (var_info);
}

// key, var_info, op, var
// key, value, attr, op, var -> register
t_var_info	*var_create_var_info_for_set(t_var *var, \
											const char *key, \
											char *value, \
											t_var_attr attr)
{
	t_var_info	*var_info;

	attr = get_declare_attr(var, key, attr);
	value = update_value_based_on_key(var, key, value);
	var_info = var_create_var_info(value, attr);
	ft_free(&value);
	return (var_info);
}
