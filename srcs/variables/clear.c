#include "minishell.h"
#include "ms_var.h"
#include "ft_hash.h"

void	env_clear(t_var *var)
{
	hs_clear(&var->hash);
}
