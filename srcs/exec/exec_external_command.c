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
	if (tmp_err == ENOTDIR)
		return (STATUS_NOT_A_DIRECTORY); // 126
	if (tmp_err == ENOENT)
		return (STATUS_NO_SUCH_FILE); // 127
	return (1);// todo:tmp
}

static uint8_t	err_cmd_not_found_and_ret_status(const char *const cmd, \
													t_context *context, \
													char **exec_path)
{
	puterr_cmd_msg_set_status(\
		cmd, ERROR_MSG_CMD_NOT_FOUND, context, STATUS_CMD_NOT_FOUND);
	ft_free(exec_path);
	return (context->status);
}

static uint8_t	err_is_a_dir_and_ret_status(const char *const cmd, \
											t_context *context, \
											char **exec_path)
{
	puterr_cmd_msg_set_status(\
		cmd, strerror(EISDIR), context, STATUS_IS_A_DIRECTORY);
	ft_free(exec_path);
	return (context->status);
}

uint8_t	execute_external_command(char *const *argv, t_context *context)
{
	char	*exec_path;
	char	**envp;
	t_var	*var;

	if (!argv[0])
		return (REDIRECT_ONLY_SUCCESS);
	var = context->var;
	exec_path = create_exec_path((const char *const *)argv, var);
	if (!exec_path)
		return (err_cmd_not_found_and_ret_status(argv[0], context, &exec_path));
	else if (is_a_directory(exec_path))
		return (err_is_a_dir_and_ret_status(argv[0], context, &exec_path));
	envp = var->convert_to_envp(var);
	errno = 0;
	if (execve(exec_path, (char *const *)argv, envp) == EXECVE_ERROR)
		puterr_cmd_msg_set_status(\
		argv[0], strerror(errno), context, set_execve_status(errno));
	ft_free(&exec_path);
	free_2d_array(&envp);
	return (context->status);
}
