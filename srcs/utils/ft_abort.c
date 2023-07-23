#include <signal.h>
#include <stdlib.h>
#include "minishell.h"

void	ft_abort(void)
{
	exit(STATUS_SIG_BASE + SIGABRT);
}
