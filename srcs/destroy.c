#include <readline/readline.h>
#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

void	destroy(t_context context)
{
	context.var->clear(context.var);
	ft_free(&context.var);
	ft_free(&context.internal_pwd);
	rl_clear_history();
}
