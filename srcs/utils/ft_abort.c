#include <stdlib.h>
#include <signal.h>
#include "minishell.h"

void	ft_abort(void)
{
	exit(STATUS_SIG_BASE + SIGABRT);
}
