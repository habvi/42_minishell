#include <errno.h>
#include <sys/stat.h>
#include "minishell.h"

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
