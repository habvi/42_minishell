#include "minishell.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_string.h"

static char	*join_new_value(char *pre, char *new)
{
	char	*joined;

	joined = ft_strjoin(pre, new);
	if (!joined)
		ft_abort();
	return (joined);
}

// call from only export -> attr is VAR_ENV
static void	env_join_value_update(t_var *var, \
									char *key, \
									t_var_info *var_info, \
									t_deque_node *node)
{
	t_elem		*elem;
	t_var_info	*info;
	t_var_info	*new_info;
	char		*joined_value;

	elem = (t_elem *)node->content;
	info = (t_var_info *)elem->value;
	joined_value = join_new_value(info->value, var_info->value);
	new_info = env_create_var_info(joined_value, VAR_ENV);
	hs_update_value(&key, new_info, node, var->hash->del_hash_value);
	del_var_info((void **)&var_info);
	ft_free(&joined_value);
}

// allocate dup_key, dup_info
void	env_join(t_var *var, const char *key, const t_var_info *var_info)
{
	t_deque_node	*target_node;
	char			*dup_key;
	t_var_info		*dup_info;

	env_dup_key_info_pair(key, var_info, &dup_key, &dup_info);
	target_node = hs_find_key(var->hash, dup_key);
	if (target_node)
		env_join_value_update(var, dup_key, dup_info, target_node);
	else
	{
		if (hs_add_to_table(var->hash, dup_key, dup_info) == HASH_ERROR)
			ft_abort();
	}
}

void	env_create_info_join(t_var *var, \
								const char *key, \
								const char *value, \
								t_var_attr attr)
{
	t_var_info	*info;

	info = env_create_var_info(value, attr);
	env_join(var, key, info);
	del_var_info((void **)&info);
}
