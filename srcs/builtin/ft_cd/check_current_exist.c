#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_string.h"

t_result	cd_check_current_exist(const char *internal_pwd)
{
	char	*cwd;
	int		tmp_err;

	if (internal_pwd)
		return (CONTINUE);
	cwd = get_current_path(&tmp_err);
	ft_free((void **)&cwd);
	if (tmp_err)
	{
		if (tmp_err == ENOENT)
		{
			puterr_whom_cmd_arg_msg(CHDIR, \
									ERROR_MSG_RETRIEVE_CWD, \
									ERROR_MSG_GETCWD, \
									strerror(tmp_err));
			return (FAILURE);
		}
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

// chdir's result == FAILURE
//   -> new_pwd is pwd + path (just joined) and no error handling.
t_result	cd_check_new_path_exist(const char *arg, \
									char **new_path, \
									const char *path, \
									const char *internal_pwd)
{
	t_result	result;
	int			tmp_err;
	char		*cwd;
	char		*tmp;

	result = cd_exec_chdir(*new_path, &tmp_err);
	if (result == PROCESS_ERROR || result == SUCCESS)
		return (result);
	cwd = get_working_directory(CMD_CD, &result);
	if (tmp_err)
	{
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		tmp = *new_path;
		*new_path = x_ft_strjoin(internal_pwd, PATH_DELIMITER_STR);
		*new_path = extend_str(*new_path, x_ft_strdup(path));
		ft_free((void **)&tmp);
		return (SUCCESS);
	}
	puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
	ft_free((void **)&cwd);
	return (FAILURE);
}
