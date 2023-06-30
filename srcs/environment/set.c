#include "minishell.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

// todo: fatal error

// key=
//static void	env_add(t_env *env, char *key, char *value, t_deque_node *node)
//{
//	if (!value)
//	{
//		ft_free(&key);
//		return ;
//	}
//	hs_update_value(&key, value, node, env->hash->del_hash_value);
//}

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
}

//void	env_set(t_env *env, char *key, char *value, t_env_op op)
//{
//	t_deque_node	*target_node;
//
//	target_node = hs_find_key(env->hash, key);
//	if (target_node)
//	{
//		if (op == ENV_ADD)
//			env_add(env, key, value, target_node);
//		else if (op == ENV_JOIN)
//			env_join(env, key, value, target_node);
//	}
//	else
//	{
//		if (hs_add_to_table(env->hash, key, value) == HASH_ERROR)
//			ft_abort();
//	}
//}

//////////////////////////////////////////////////////////////////////////////

void	env_create_info_add(t_env *env, const char *key, const char *value, t_var_attr attr)
{
	t_var_info	*info;

	info = env_create_var_info(value, attr);
	env_add(env, key, info);
	del_var_info(&info);
}

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

static void	dup_key_info_pair(const char *key, const t_var_info *info, char **dup_key, t_var_info **dup_info)
{
	*dup_key = ft_strdup_abort(key);
	*dup_info = dup_var_info(info);
}

// allocate dup_key, dup_info
void	env_add(t_env *env, const char *key, const t_var_info *info)
{
	t_deque_node	*target_node;
	char			*dup_key;
	t_var_info		*dup_info;

	dup_key_info_pair(key, info, &dup_key, &dup_info);
	target_node = hs_find_key(env->hash, dup_key);
	if (target_node)
	{
		if (!dup_info)
		{
			ft_free(&dup_key);
			return ;
		}
		hs_update_value(&dup_key, dup_info, target_node, env->hash->del_hash_value);
	}
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

// allocate dup_key, dup_info
void	env_join(t_env *env, const char *key, const t_var_info *var_info)
{
	t_deque_node	*target_node;
	char			*dup_key;
	t_var_info		*dup_info;

	dup_key_info_pair(key, var_info, &dup_key, &dup_info);
	target_node = hs_find_key(env->hash, dup_key);
	if (target_node)
	{
		env_join_value_update(env, dup_key, dup_info, target_node);
		del_var_info(&dup_info);
	}
	else
	{
		if (hs_add_to_table(env->hash, dup_key, dup_info) == HASH_ERROR)
			ft_abort();
	}
}