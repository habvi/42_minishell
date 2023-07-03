#include <dirent.h>
#include <errno.h>
#include "minishell.h"

static bool	test_opendir(const char *path, int *tmp_err)
{
	DIR	*dirp;

	errno = 0;
	dirp = opendir(path);
	*tmp_err = errno;
	closedir(dirp);
	if (*tmp_err != 0)
		return (false);
	return (true);
}

static bool	is_permission_denied(int tmp_err)
{
	return (tmp_err == EACCES);
}

bool	is_valid_path(const char *path, int *tmp_err)
{
	if (test_opendir(path, tmp_err))
		return (true);
	if (is_permission_denied(*tmp_err))
		return (true);
	return (false);
}
