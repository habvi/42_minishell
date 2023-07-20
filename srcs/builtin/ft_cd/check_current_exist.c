#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

static t_result	check_current_exist_inter(const char *arg, char **new_path)
{
	t_result	result;
	int			tmp_err;
	char		*cwd;

	result = cd_exec_chdir(*new_path, &tmp_err);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (result == FAILURE)
	{
		cwd = get_working_directory(CMD_CD);
		if (cwd)
		{
			ft_free(&cwd);
			puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
			return (FAILURE);
		}
		return (BREAK);
	}
	return (SUCCESS);
}

// result == BREAK : new_pwd is pwd/path (just joined) and no error returns.
t_result	check_current_exist(const char *arg, \
								char **new_path, \
								const char *internal_pwd, \
								const char *path)
{
	t_result	result;
	int			tmp_err;

	result = check_current_exist_inter(arg, new_path);
	if (result == PROCESS_ERROR || result == FAILURE)
	{
		ft_free(new_path);
		cd_exec_chdir(internal_pwd, &tmp_err);
	}
	else if (result == BREAK)
	{
		ft_free(new_path);
		*new_path = x_ft_strjoin(internal_pwd, PATH_DELIMITER_STR);
		*new_path = extend_str(*new_path, x_ft_strdup(path));
		cd_exec_chdir(internal_pwd, &tmp_err);
		result = SUCCESS;
	}
	return (result);
}
