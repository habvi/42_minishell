#include <dirent.h>
#include <errno.h>
#include "minishell.h"

bool	test_opendir_strict(const char *path, t_result *result)
{
	DIR	*dirp;

	errno = 0;
	dirp = opendir(path);
	if (dirp)
		*result = SUCCESS;
	else if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
		*result = FAILURE;
	else
		*result = PROCESS_ERROR;
	if (!dirp)
		return (false);
	if (closedir(dirp) == CLOSE_ERROR)
	{
		*result = PROCESS_ERROR;
		return (false);
	}
	return (true);
}

static t_result	try_opendir(const char *path, int *tmp_err)
{
	DIR	*dirp;

	errno = 0;
	dirp = opendir(path);
	*tmp_err = errno;
	if (dirp)
	{
		if (closedir(dirp) == CLOSE_ERROR)
			return (PROCESS_ERROR);
		return (SUCCESS);
	}
	if (*tmp_err == EACCES || *tmp_err == ENOENT || *tmp_err == ENOTDIR)
		return (FAILURE);
	return (PROCESS_ERROR);
}

static bool	is_permission_denied(int tmp_err)
{
	return (tmp_err == EACCES);
}

bool	is_valid_path(const char *path, int *tmp_err, t_result *result)
{
	t_result	open_result;

	*result = SUCCESS;
	open_result = try_opendir(path, tmp_err);
	if (open_result == PROCESS_ERROR)
	{
		*result = PROCESS_ERROR;
		return (false);
	}
	if (open_result == SUCCESS)
		return (true);
	if (is_permission_denied(*tmp_err))
		return (true);
	return (false);
}

bool	is_a_directory(const char *path, t_result *result)
{
	int			tmp_err;
	t_result	open_res;

	*result = SUCCESS;
	if (!path || !is_a_directory_by_stat(path, result))
		return (false);
	open_res = try_opendir(path, &tmp_err);
	if (open_res == PROCESS_ERROR)
	{
		*result = PROCESS_ERROR;
		return (false);
	}
	if (open_res == SUCCESS)
		return (true);
	if (is_permission_denied(tmp_err))
		return (true);
	return (false);
}
