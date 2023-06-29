#include "minishell.h"
#include "ft_string.h"
#include "ft_mem.h"

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
	env->set(env, dup_key, dup_value, op);
}
