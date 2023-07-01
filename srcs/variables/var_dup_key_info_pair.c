#include "minishell.h"
#include "ms_var.h"
#include "ft_string.h"
#include "ft_sys.h"

char	*ft_strdup_abort(const char *str)
{
	char	*dup;

	if (!str)
		return (NULL);
	dup = ft_strdup(str);
	if (!dup)
		ft_abort();
	return (dup);
}

// todo var_?
static t_var_info	*dup_var_info(const t_var_info *var_info)
{
	t_var_info	*dup_info;

	if (!var_info)
		return (NULL);
	dup_info = (t_var_info *)x_malloc(sizeof(t_var_info));
	if (!dup_info)
		ft_abort();
	dup_info->value = ft_strdup_abort(var_info->value);
	dup_info->attr = var_info->attr;
	return (dup_info);
}

void	var_dup_key_info_pair(const char *key, \
								const t_var_info *var_info, \
								char **dup_key, \
								t_var_info **dup_info)
{
	*dup_key = ft_strdup_abort(key);
	*dup_info = dup_var_info(var_info);
}
