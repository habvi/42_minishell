#include "minishell.h"

void	puterr_msg(const char *msg)
{
	ft_dprintf(STDERR_FILENO, \
				"%s: %s\n", \
				SHELL_NAME, msg);
}
