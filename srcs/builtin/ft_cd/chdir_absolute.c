#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"
#include "ft_mem.h"

t_result	cd_chdir_from_absolute_path(const char *path, char **absolute_path)
{
	t_result	result;
	int			tmp_err;

	*absolute_path = x_ft_strdup(path);
	result = cd_change_dir_to_valid_path(path, &tmp_err);
	if (result == FAILURE)
	{
		if (tmp_err == EACCES)
		{
			puterr_cmd_arg_msg(CMD_CD, path, strerror(tmp_err));
			// ft_dprintf(2, "%d: [%s]\n", __LINE__, *absolute_path);
		}
		return (FAILURE);
	}
	ft_free(absolute_path);
	*absolute_path = cd_canonicalize_path(path, NULL);
	return (SUCCESS);
}
