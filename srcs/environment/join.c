#include "minishell.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"

static char	*join_new_value(char *pre, char *new)
{
	char	*joined;

	joined = ft_strjoin(pre, new);
	if (!joined)
		ft_abort();
	return (joined);
}

// key expected `name` -> void ...?
// key+=
// todo: attr -x + --
static void	env_join_value_update(t_env *env, char *key, t_var_info *var_info, t_deque_node *node)
{
	t_elem		*elem;
	t_var_info	*info;
	char		*joined_value;

	elem = (t_elem *)node->content;
	info = (t_var_info *)elem->value;
	joined_value = join_new_value(info->value, var_info->value); // s1 + s2
	hs_update_value(&key, joined_value, node, env->hash->del_hash_value);
	del_var_info(&var_info);
}

// allocate dup_key, dup_info
void	env_join(t_env *env, const char *key, const t_var_info *var_info)
{
	t_deque_node	*target_node;
	char			*dup_key;
	t_var_info		*dup_info;

	dup_key_info_pair(key, var_info, &dup_key, &dup_info);
	target_node = hs_find_key(env->hash, dup_key);
	if (target_node)
		env_join_value_update(env, dup_key, dup_info, target_node);
	else
	{
		if (hs_add_to_table(env->hash, dup_key, dup_info) == HASH_ERROR)
			ft_abort();
	}
}

//
void	env_create_info_join(t_env *env, const char *key, const char *value, t_var_attr attr)
{
	t_var_info	*info;

	info = env_create_var_info(value, attr);
	env_join(env, key, info);
	del_var_info(&info);
}
