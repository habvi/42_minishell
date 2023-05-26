#include "minishell.h"
#include "deque.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "ft_string.h"
#include "ft_builtin.h"

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
	if (command[0] && ft_strncmp(command[0], "echo", 5) == 0)
	{
//		dprintf(STDERR_FILENO, "exec ft_echo");
		ft_echo(command);
		deque_clear_all(&cmd->head_command);
		exit(EXIT_SUCCESS);
	}
	if (execve(command[0], command, environ) == EXECVE_ERROR)
	{
		// write or malloc error..?
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
											command[0], EXIT_MSG_NO_SUCH_FILE);
		deque_clear_all(&cmd->head_command);
		exit(EXIT_CODE_NO_SUCH_FILE);
	}
}
