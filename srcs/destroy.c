#include <readline/readline.h>
#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

void	destroy_context(t_context context) // todo
{
	context.var->clear(context.var);
	ft_free((void **)&context.var);
	ft_free((void **)&context.internal_pwd);
	rl_clear_history();
}
