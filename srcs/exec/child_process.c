#include "minishell.h"
#include "ft_dprintf.h"
#include "libft.h"

// use PROMPT_NAME
void	child_process(char **commands, char **environ)
{
	debug_func(__func__, __LINE__);
	debug_2d_array(commands);
	// if (!commands[0])
	// 	exit(EXIT_SUCCESS);
	if (execve(commands[0], commands, environ) == EXECVE_ERROR)
	{
		// write or malloc error
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
											commands[0], EXIT_MSG_NO_SUCH_FILE);
		free_2d_array(&commands);
		exit(EXIT_CODE_NO_SUCH_FILE);
	}
}
