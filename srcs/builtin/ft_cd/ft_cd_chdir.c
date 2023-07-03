#include <unistd.h>
#include "minishell.h"
#include "ms_builtin.h"

bool	is_absolute_path(const char *path)
{
	return (path[0] == ABSOLUTE_PATH_HEAD);
}

static t_result	exec_chdir(const char *path, uint8_t *status)
{
	if (chdir(path) == CHDIR_ERROR)
	{
		*status = 1; // todo
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

// if chdir error, no need for auto perror.
// "pwd + path" -> "path"
t_result	cd_change_dir_to_valid_path(const char *absolute_path, \
										uint8_t *status)
{
	if (exec_chdir(absolute_path, status) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
