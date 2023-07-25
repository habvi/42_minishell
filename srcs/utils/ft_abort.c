#include <signal.h>
#include <stdlib.h>
#include "minishell.h"

void	ft_abort(void)
{
	puterr_msg(ERROR_MSG_ABORT);
	exit(STATUS_SIG_BASE + SIGABRT);
}
