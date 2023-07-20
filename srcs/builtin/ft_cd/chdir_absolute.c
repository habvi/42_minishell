#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"
#include "ft_mem.h"

t_result	cd_chdir_from_absolute_path(char **absolute_path, const char *path)
{
	t_result	result;
	int			tmp_err;

	*absolute_path = x_ft_strdup(path);
	result = cd_exec_chdir(path, &tmp_err);
	if (result == PROCESS_ERROR || result == FAILURE)
	{
		puterr_cmd_arg_msg(CMD_CD, path, strerror(tmp_err));
		ft_free(absolute_path);
		return (result);
	}
	ft_free(absolute_path);
	*absolute_path = cd_canonicalize_path(path, NULL);
	return (SUCCESS);
}
