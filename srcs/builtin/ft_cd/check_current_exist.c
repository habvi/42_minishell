#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_mem.h"

void	set_absolute_path_in_error(char **absolute_path, \
									const char *backup_pwd, \
									const char *path, \
									t_result result)
{
	ft_free(absolute_path);
	if (result == FAILURE)
		*absolute_path = x_ft_strdup(backup_pwd);
	else if (result == BREAK)
	{
		*absolute_path = x_ft_strjoin(backup_pwd, PATH_DELIMITER_STR);
		*absolute_path = extend_str(*absolute_path, x_ft_strdup(path));
	}
}

t_result	check_current_exist(const char *arg, char **canonicalized_path)
{
	t_result	result;
	int			tmp_err;
	char		*cwd;

	result = cd_exec_chdir(*canonicalized_path, &tmp_err);
	if (result == SUCCESS)
		return (SUCCESS);
	cwd = get_working_directory(CMD_CD);
	if (cwd)
	{
		ft_free(&cwd);
		puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
		return (FAILURE);
	}
	return (BREAK);
}
