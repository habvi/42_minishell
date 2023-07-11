#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_var.h"
#include "ft_dprintf.h"
#include "ft_mem.h"

static uint8_t	set_execve_status(int tmp_err)
{
	if (tmp_err == EACCES)
		return (STATUS_PERMISSION); // 126
	if (tmp_err == ENOENT)
		return (STATUS_NO_SUCH_FILE); // 127
	return (1);// todo:tmp
}

static void	error_cmd_not_found(char *const cmd, t_context *context)
{
	context->status = STATUS_CMD_NOT_FOUND;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", \
					SHELL_NAME, cmd, ERROR_MSG_CMD_NOT_FOUND);
}

static void	error_execve(char *const cmd, int tmp_err, t_context *context)
{
	context->status = set_execve_status(tmp_err);
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", \
					SHELL_NAME, cmd, strerror(tmp_err));
}

uint8_t	execute_external_command(char *const *argv, t_context *context)
{
	char	*exec_path;
	char	**envp;
	t_var	*var;

	if (!argv[0])
		return (0); // todo: ok? case:redirect only
	var = context->var;
	exec_path = create_exec_path((const char *const *)argv, var);
	if (!exec_path)
	{
		error_cmd_not_found(argv[0], context);
		ft_free(&exec_path);
		return (context->status);
	}
	envp = var->convert_to_envp(var);
	errno = 0;
	if (execve(exec_path, (char *const *)argv, envp) == EXECVE_ERROR)
		error_execve(argv[0], errno, context);
	ft_free(&exec_path);
	free_2d_array(&envp);
	return (context->status);
}
