#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

static int	execute_builtin_command(t_command *cmd, t_params *params)
{
	char *const	*command = (char *const *)cmd->exec_command;
	int			exec_status;

	exec_status = call_builtin_command(command, params);
	deque_clear_all(&cmd->head_command);
	return (exec_status);
}

static int	execute_external_command(t_command *cmd, char **environ)
{
	char *const	*command = cmd->exec_command;
	int			exec_status;

	exec_status = execve(command[0], command, environ);
	if (exec_status == EXECVE_ERROR)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
			command[0], ERROR_MSG_CMD_NOT_FOUND);
		deque_clear_all(&cmd->head_command);
	}
	return (EXIT_CODE_NO_SUCH_FILE);
}

// use PROMPT_NAME
// if execve erorr, no need for auto perror.
void	child_process(t_command *cmd, \
						t_fd *fd, \
						char **environ, \
						t_params *params)
{
	char	**command;

	command = cmd->exec_command;
	// debug_func(__func__, __LINE__);
	// debug_2d_array(command);
	if (handle_child_pipes(cmd, fd) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	if (is_command_builtin(command[0]))
		exit (execute_builtin_command(cmd, params));
	else
		exit (execute_external_command(cmd, environ));
}
