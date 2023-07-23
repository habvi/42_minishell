#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_string.h"

// todo: err_arg
static void	puterr_arg_or_path(const char *arg, const char *path, int tmp_err)
{
	const char	*err_arg;

	if (!path)
	{
		if (!arg || ft_streq(arg, KEY_HOME) || ft_streq(arg, CD_ARG_HOME))
			err_arg = KEY_HOME;
		else
			err_arg = KEY_OLDPWD;
		puterr_cmd_arg_msg_wo_colon(CMD_CD, err_arg, ERROR_MSG_NOT_SET);
	}
	else
		puterr_cmd_arg_msg(CMD_CD, path, strerror(tmp_err));
}

static bool	is_valid_directory_failure(const int tmp_err)
{
	return (tmp_err == EACCES || tmp_err == ENOENT || tmp_err == ENOTDIR);
}

t_result	chack_is_valid_directory(const char *arg, \
										const char *path, \
										char *new_path, \
										const bool is_contain_dot)
{
	int	tmp_err;

	if (!test_opendir(new_path, &tmp_err))
	{
		if (!is_valid_directory_failure(tmp_err))
			return (PROCESS_ERROR);
		if (tmp_err == EACCES)
		{
			puterr_arg_or_path(arg, path, tmp_err);
			return (FAILURE);
		}
		if (is_contain_dot)
			return (SUCCESS);
		puterr_arg_or_path(arg, path, tmp_err);
		return (FAILURE);
	}
	return (SUCCESS);
}
