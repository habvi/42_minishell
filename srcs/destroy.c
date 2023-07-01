#include <readline/readline.h>
#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

void	destroy(t_context context)
{
	context.env->clear(context.env);
	ft_free(&context.env);
	ft_free(&context.internal_pwd);
	rl_clear_history();
}
