#include "minishell.h"
#include "ms_var.h"
#include "ft_hash.h"

// always success
void	var_unset(t_var *var, const char *key)
{
	hs_delete_key(var->hash, key);
}
