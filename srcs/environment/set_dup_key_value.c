#include "minishell.h"
#include "ft_string.h"
#include "ft_mem.h"

#include "ft_dprintf.h"
#include "ft_deque.h"
#include "ft_hash.h"

// key : valid key
void	env_set_dup_key_value(t_env *env, \
								const char *key, \
								const char *value, \
								t_env_op op)
{
	char	*dup_key;
	char	*dup_value;

	dup_key = ft_strdup(key);
	if (!dup_key)
		ft_abort();
	dup_value = NULL;
	if (value)
	{
		dup_value = ft_strdup(value);
		if (!dup_value)
			ft_abort();
	}
	// ft_dprintf(2, "dup_key: %s, dup_value: %s\n", dup_key, dup_value);
	env->set(env, dup_key, dup_value, op);
}

// key : valid key
void	env_set_dup_key_value_allow_null(t_env *env, \
											const char *key, \
											const char *value, \
											t_env_op op)
{
	char	*dup_key;
	char	*dup_value;

	dup_key = ft_strdup(key);
	if (!dup_key)
		ft_abort();
	dup_value = NULL;
	if (value)
	{
		dup_value = ft_strdup(value);
		if (!dup_value)
			ft_abort();
	}

	(void)op;
	t_deque_node	*target_node;

	target_node = hs_find_key(env->hash, key);
	hs_update_value(&dup_key, dup_value, target_node, env->hash->del_value);
}
