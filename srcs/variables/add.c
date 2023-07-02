#include "minishell.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

// allocate dup_key, dup_info
void	var_add(t_var *var, const char *key, const t_var_info *var_info)
{
	t_deque_node	*target;
	char			*dup_key;
	t_var_info		*dup_info;

	var_dup_key_info_pair(key, var_info, &dup_key, &dup_info);
	target = hs_find_key(var->hash, dup_key);
	if (target)
		hs_update_value(&dup_key, dup_info, target, var->hash->del_hash_value);
	else
	{
		if (hs_add_to_table(var->hash, dup_key, dup_info) == HASH_ERROR)
			ft_abort();
	}
}

void	var_create_info_add(t_var *var, \
							const char *key, \
							const char *value, \
							t_var_attr attr)
{
	t_var_info	*var_info;

	var_info = var_create_var_info(value, attr);
	var_add(var, key, var_info);
	del_var_info((void **)&var_info);
}
