#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

static uint8_t	execute_builtin_command(t_command *cmd, t_params *params)
{
	const char *const	*argv = (const char *const *)cmd->exec_command;
	uint8_t				exec_status;

	exec_status = call_builtin_command(argv, params);
	deque_clear_all(&cmd->head_command, free);
	return (exec_status);
}

static uint8_t	execute_external_command(t_command *cmd, char **environ)
{
	char *const	*argv = cmd->exec_command;
	int			exec_status;

	if (argv[0])
		exec_status = execve(argv[0], argv, environ);
	if (!argv[0] || exec_status == EXECVE_ERROR)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", \
					SHELL_NAME, argv[0], ERROR_MSG_CMD_NOT_FOUND);
		deque_clear_all(&cmd->head_command, free);
	}
	return (EXIT_CODE_NO_SUCH_FILE);
}

// if execve erorr, no need for auto perror.
void	child_process(t_command *cmd, \
						t_fd *fd, \
						char **environ, \
						t_params *params)
{
	char *const	*argv = cmd->exec_command;

	// debug_func(__func__, __LINE__);
	// debug_2d_array(argv);
	if (handle_child_pipes(cmd, fd) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	if (is_command_builtin(argv[0]))
		exit(execute_builtin_command(cmd, params));
	else
		exit(execute_external_command(cmd, environ));
}
