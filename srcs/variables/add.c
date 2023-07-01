#include "minishell.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

// allocate dup_key, dup_info
void	env_add(t_env *env, const char *key, const t_var_info *info)
{
	t_deque_node	*target;
	char			*dup_key;
	t_var_info		*dup_info;

	env_dup_key_info_pair(key, info, &dup_key, &dup_info);
	target = hs_find_key(env->hash, dup_key);
	if (target)
	{
		if (!dup_info)
		{
			ft_free(&dup_key);
			return ;
		}
		hs_update_value(&dup_key, dup_info, target, env->hash->del_hash_value);
	}
	else
	{
		if (hs_add_to_table(env->hash, dup_key, dup_info) == HASH_ERROR)
			ft_abort();
	}
}

void	env_create_info_add(t_env *env, \
							const char *key, \
							const char *value, \
							t_var_attr attr)
{
	t_var_info	*info;

	info = env_create_var_info(value, attr);
	env_add(env, key, info);
	del_var_info((void **)&info);
}
