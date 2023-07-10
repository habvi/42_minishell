#include <dirent.h>
#include <errno.h>
#include "minishell.h"

bool	test_opendir_strict(const char *path)
{
	DIR	*dirp;

	dirp = opendir(path);
	if (!dirp)
		return (false);
	closedir(dirp);
	return (true);
}

static bool	test_opendir(const char *path, int *tmp_err)
{
	DIR	*dirp;

	errno = 0;
	dirp = opendir(path);
	*tmp_err = errno;
	if (*tmp_err != 0)
		return (false);
	closedir(dirp);
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
