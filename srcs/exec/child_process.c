#include "minishell.h"
#include "ft_dprintf.h"
#include "libft.h"

// use PROMPT_NAME
// if execve erorr, no need for auto perror.
void	child_process(t_command *cmd, t_fd *fd, char **environ)
{
	char	**command;

	command = cmd->exec_command;
	// debug_func(__func__, __LINE__);
	// debug_2d_array(command);
	// if (!command[0])
	// 	exit(EXIT_SUCCESS);
	if (handle_child_pipes(cmd, fd) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	if (execve(command[0], command, environ) == EXECVE_ERROR)
	{
		// write or malloc error..?
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
											command[0], EXIT_MSG_NO_SUCH_FILE);
		// leaks
		free_2d_array(&cmd->head);
		exit(EXIT_CODE_NO_SUCH_FILE);
	}
}
