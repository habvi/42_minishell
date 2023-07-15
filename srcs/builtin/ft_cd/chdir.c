#include <errno.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_builtin.h"

bool	is_absolute_path(const char *path)
{
	return (path[0] == ABSOLUTE_PATH_HEAD);
}

static t_result	exec_chdir(const char *path, int *tmp_err)
{
	errno = 0;
	if (chdir(path) == CHDIR_ERROR)
	{
		*tmp_err = errno;
		return (PROCESS_ERROR);
	}
	*tmp_err = errno;
	return (SUCCESS);
}

// if chdir error, no need for auto perror.
// "pwd + path" -> "path"
t_result	cd_change_dir_to_valid_path(const char *absolute_path, \
										int *tmp_err)
{
	if (exec_chdir(absolute_path, tmp_err) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
