#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_var.h"
#include "ft_mem.h"
#include "ft_string.h"

static uint8_t	set_execve_status(int tmp_err)
{
	if (tmp_err == EACCES)
		return (STATUS_PERMISSION); // 126
	if (tmp_err == ENOTDIR)
		return (STATUS_NOT_A_DIRECTORY); // 126
	if (tmp_err == ENOENT)
		return (STATUS_NO_SUCH_FILE); // 127
	return (EXIT_FAILURE);
}

static size_t	get_paths_len(t_var *var)
{
	size_t	len;
	char	*paths;

	paths = var->get_value(var, KEY_PATH);
	len = ft_strlen(paths);
	ft_free((void **)&paths);
	return (len);
}

uint8_t	execute_external_command(char *const *argv, t_context *context)
{
	const char *const	command = argv[0];
	t_var				*var;
	char				*exec_path;
	const size_t		paths_len = get_paths_len(context->var);
	char				**envp;

	if (!command)
		return (REDIRECT_ONLY_SUCCESS);
	var = context->var;
	exec_path = create_exec_path(\
			(const char *const *)argv, var, paths_len, context);
	if (!exec_path)
		return (context->status);
	envp = var->convert_to_envp(var);
	errno = 0;
	if (execve(exec_path, (char *const *)argv, envp) == EXECVE_ERROR)
	{
		puterr_cmd_msg_set_status(\
			exec_path, strerror(errno), context, set_execve_status(errno));
	}
	ft_free((void **)&exec_path);
	free_2d_array(&envp);
	return (context->status);
}
