#include "minishell.h"
#include "ft_dprintf.h"
#include "libft.h"

// use PROMPT_NAME
void	child_process(t_command *cmd, int pipefd[2], int prev_fd, char **environ)
{
	char	**command;

	(void)pipefd;
	(void)prev_fd;
	command = cmd->exec_command;
	debug_func(__func__, __LINE__);
	debug_2d_array(command);
	// if (!command[0])
	// 	exit(EXIT_SUCCESS);
	if (execve(command[0], command, environ) == EXECVE_ERROR)
	{
		// write or malloc error
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
											command[0], EXIT_MSG_NO_SUCH_FILE);
		free_2d_array(&cmd->head);
		exit(EXIT_CODE_NO_SUCH_FILE);
	}
}
