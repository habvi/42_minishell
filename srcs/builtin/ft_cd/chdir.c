#include <errno.h>
#include "minishell.h"

static bool	is_chdir_failure(const int tmp_err)
{
	return (tmp_err == EACCES || tmp_err == ENOENT \
			|| tmp_err == ENOTDIR || tmp_err == ELOOP \
			|| tmp_err == ENAMETOOLONG);
}

// if chdir error, no need for auto perror.
t_result	cd_exec_chdir(const char *path, int *tmp_err)
{
	*tmp_err = 0;
	errno = 0;
	if (chdir(path) == CHDIR_ERROR)
	{
		*tmp_err = errno;
		if (is_chdir_failure(*tmp_err))
			return (FAILURE);
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
