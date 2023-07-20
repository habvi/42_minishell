#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_builtin.h"

static bool	is_chdir_failure(int tmp_err)
{
	return (tmp_err == EACCES || tmp_err == ENOENT \
			|| tmp_err == ENOTDIR || tmp_err == ELOOP \
			|| tmp_err == ENAMETOOLONG);
}

// if chdir error, no need for auto perror.
t_result	cd_exec_chdir(const char *absolute_path, int *tmp_err)
{
	*tmp_err = 0;
	errno = 0;
	if (chdir(absolute_path) == CHDIR_ERROR)
	{
		*tmp_err = errno;
		if (is_chdir_failure(*tmp_err))
			return (FAILURE);
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

t_result	try_change_directory(const char *arg, \
									char *canonicalized_path, \
									bool is_contain_dot)
{
	t_result	result;
	int			tmp_err;

	result = cd_exec_chdir(canonicalized_path, &tmp_err);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (result == FAILURE)
	{
		if (tmp_err == EACCES)
		{
			puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
			return (FAILURE);
		}
		if (is_contain_dot)
			return (SUCCESS);
		puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
		return (FAILURE);
	}
	return (SUCCESS);
}
