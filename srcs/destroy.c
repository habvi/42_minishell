#include <readline/readline.h>
#include "minishell.h"
#include "ft_hash.h"
#include "ft_mem.h"

void	destroy(t_params params)
{
	hs_clear(&params.env->hash);
	ft_free(params.env);
	rl_clear_history();
}
