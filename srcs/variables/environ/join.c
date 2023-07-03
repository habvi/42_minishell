#include "minishell.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_string.h"

static char	*create_joined_value(t_deque_node *node, char *new_value)
{
	t_elem		*elem;
	t_var_info	*existing_info;
	char		*joined;

	elem = (t_elem *)node->content;
	existing_info = (t_var_info *)elem->value;
	joined = ft_strjoin(existing_info->value, new_value);
	if (!joined)
		ft_abort();
	return (joined);
}

// call from only export -> attr is VAR_ENV
static void	var_join_update_value(t_var *var, \
									char *key, \
									t_var_info *var_info, \
									t_deque_node *existing_node)
{
	t_var_info	*new_info;
	char		*joined_value;

	joined_value = create_joined_value(existing_node, var_info->value);
	new_info = var_create_var_info(joined_value, VAR_ENV);
	hs_update_value(&key, new_info, existing_node, var->hash->del_hash_value);
	del_var_info((void **)&var_info);
	ft_free(&joined_value);
}

// allocate key, value
void	var_join(t_var *var, \
					const char *key, \
					const char *value, \
					t_var_attr attr)
{
	t_deque_node	*target_node;
	char			*dup_key;
	t_var_info		*var_info;

	var_info = var_create_var_info_for_set(var, key, value, attr);
	dup_key = x_ft_strdup(key);
	target_node = hs_find_key(var->hash, dup_key);
	if (target_node)
		var_join_update_value(var, dup_key, var_info, target_node);
	else
	{
		if (hs_add_to_table(var->hash, dup_key, var_info) == HASH_ERROR)
			ft_abort();
	}
}
