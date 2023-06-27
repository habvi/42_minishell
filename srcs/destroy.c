#include <readline/readline.h>
#include "minishell.h"
#include "ft_mem.h"

void	destroy(t_params params)
{
	params.env->clear(params.env);
	ft_free(&params.env);
	ft_free(&params.pwd);
	ft_free(&params.old_pwd);
	rl_clear_history();
}
