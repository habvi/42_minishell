#include <readline/readline.h>
#include "minishell.h"
#include "ft_hash.h"
#include "ft_mem.h"

void	destroy(t_params params)
{
	hs_clear(&params.env->hash);
	ft_free(&params.env);
	ft_free(&params.pwd);
	ft_free(&params.old_pwd);
	rl_clear_history();
}
