#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
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

static t_result	try_opendir(const char *path, int *tmp_err)
{
	DIR	*dirp;

	errno = 0;
	dirp = opendir(path);
	*tmp_err = errno;
	if (*tmp_err == 0)
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

static t_result	get_stat_result(int tmp_err)
{
	if (tmp_err == 0)
		return (SUCCESS);
	if (tmp_err == EACCES || tmp_err == ENOENT || tmp_err == ENOTDIR)
		return (FAILURE);
	return (PROCESS_ERROR);
}

bool	is_file_by_stat(const char *path, t_result *result)
{
	int			stat_ret;
	bool		is_file;
	struct stat	sb;

	is_file = false;
	errno = 0;
	stat_ret = stat(path, &sb);
	*result = get_stat_result(errno);
	if (stat_ret != STAT_ERROR && S_ISREG(sb.st_mode))
		is_file = true;
	return (is_file);
}

bool	is_a_directory_by_stat(const char *path, t_result *result)
{
	int			stat_ret;
	bool		is_dir;
	struct stat	sb;

	is_dir = false;
	errno = 0;
	stat_ret = stat(path, &sb);
	*result = get_stat_result(errno);
	if (stat_ret != STAT_ERROR && S_ISDIR(sb.st_mode))
		is_dir = true;
	return (is_dir);
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
