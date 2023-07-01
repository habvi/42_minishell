#include "minishell.h"
#include "ms_var.h"
#include "ft_hash.h"

// always success
void	env_unset(t_env *env, const char *key)
{
	hs_delete_key(env->hash, key);
}
