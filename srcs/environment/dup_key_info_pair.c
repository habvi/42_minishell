#include "minishell.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

char	*ft_strdup_abort(const char *str)
{
	char	*dup;

	dup = ft_strdup(str);
	if (!*dup)
		ft_abort();
	return (dup);
}

// todo env_?
static t_var_info	*dup_var_info(const t_var_info *info)
{
	t_var_info	*dup_info;

	if (!info)
		return (NULL);
	dup_info = (t_var_info *)x_malloc(sizeof(t_var_info));
	if (!dup_info)
		ft_abort();
	dup_info->value = ft_strdup_abort(info->value);
	dup_info->attr = info->attr;
	return (dup_info);
}

void	dup_key_info_pair(const char *key, const t_var_info *info, char **dup_key, t_var_info **dup_info)
{
	*dup_key = ft_strdup_abort(key);
	*dup_info = dup_var_info(info);
}
