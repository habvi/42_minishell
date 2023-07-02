#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"
#include "ft_sys.h"
// all malloc
// key=value -> key, = ,value, attr
t_var_info	*var_create_var_info(const char *value, t_var_attr attr)
{
	t_var_info	*var_info;
	char 		*dup_value;

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
