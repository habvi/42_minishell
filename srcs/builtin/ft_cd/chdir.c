#include <errno.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_builtin.h"

// if chdir error, no need for auto perror.
// todo:
	// FAILURE: EACCES, ELOOP, ENAMETOOLONG, ENOENT, ENOTDIR
	// PROCESS_ERROR : the other
t_result	cd_exec_chdir(const char *absolute_path, int *tmp_err)
{
	errno = 0;
	if (chdir(absolute_path) == CHDIR_ERROR)
	{
		*tmp_err = errno;
		return (FAILURE);
	}
	*tmp_err = errno;
	return (SUCCESS);
}
