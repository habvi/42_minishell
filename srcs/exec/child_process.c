#include "minishell.h"
#include "ft_string.h"
#include "ft_builtin.h"
#include "deque.h"
#include "ft_dprintf.h"
#include "libft.h"

// use PROMPT_NAME
// if execve erorr, no need for auto perror.
void	child_process(t_command *cmd, t_fd *fd, char **environ)
{
	char	**command;
	int		exec_status;

	command = cmd->exec_command;
	// debug_func(__func__, __LINE__);
	// debug_2d_array(command);
	if (handle_child_pipes(cmd, fd) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	if (command && is_builtin_func(command[0]))
	{
		exec_status = call_builtin_func(command, NULL);
		deque_clear_all(&cmd->head_command);
		exit(exec_status);
	}
	if (execve(command[0], command, environ) == EXECVE_ERROR)
	{
		// write or malloc error..?
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
			command[0], ERROR_MSG_CMD_NOT_FOUND);
		deque_clear_all(&cmd->head_command);
		exit(EXIT_CODE_NO_SUCH_FILE);
	}
}
