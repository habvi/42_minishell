#include "minishell.h"
#include "ft_hash.h"

void	env_clear(t_env *env)
{
	hs_clear(&env->hash);
}
