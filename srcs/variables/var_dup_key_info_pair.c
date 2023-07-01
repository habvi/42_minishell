#include "minishell.h"
#include "ms_var.h"
#include "ft_sys.h"

// todo var_?
static t_var_info	*dup_var_info(const t_var_info *var_info)
{
	t_var_info	*dup_info;

	if (!var_info)
		return (NULL);
	dup_info = (t_var_info *)x_malloc(sizeof(t_var_info));
	if (!dup_info)
		ft_abort();
	dup_info->value = x_ft_strdup(var_info->value);
	dup_info->attr = var_info->attr;
	return (dup_info);
}

void	var_dup_key_info_pair(const char *key, \
								const t_var_info *var_info, \
								char **dup_key, \
								t_var_info **dup_info)
{
	*dup_key = x_ft_strdup(key);
	*dup_info = dup_var_info(var_info);
}
