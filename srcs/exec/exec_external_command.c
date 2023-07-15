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
		puterr_cmd_msg_set_status(\
		argv[0], ERROR_MSG_CMD_NOT_FOUND, context, STATUS_CMD_NOT_FOUND);
		ft_free(&exec_path);
		return (context->status);
	}
	envp = var->convert_to_envp(var);
	errno = 0;
	if (execve(exec_path, (char *const *)argv, envp) == EXECVE_ERROR)
		puterr_cmd_msg_set_status(\
		argv[0], strerror(errno), context, set_execve_status(errno));
	ft_free(&exec_path);
	free_2d_array(&envp);
	return (context->status);
}
