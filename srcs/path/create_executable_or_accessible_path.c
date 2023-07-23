#include <errno.h>
#include "minishell.h"
#include "ft_mem.h"

// for not pur error message, use access. not x_access.
static bool	is_accessible_command(const char *path, t_result *result)
{
	int	access_ret;

	errno = 0;
	access_ret = access(path, X_OK);
	if (access_ret != ACCESS_ERROR)
		return (true);
	if (errno == EACCES && is_file_by_stat(path, result))
		return (true);
	return (false);
}

static bool	is_executable_command(const char *path, t_result *result)
{
	int	access_ret;

	errno = 0;
	access_ret = access(path, X_OK);
	if (access_ret != ACCESS_ERROR)
		*result = SUCCESS;
	else if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
		*result = FAILURE;
	else
		*result = PROCESS_ERROR;
	return (access_ret != ACCESS_ERROR);
}

char	*create_valid_path_by_judge(char *paths, \
							const char *const arg, \
							bool (*judge)(const char *path, t_result *result),
							t_result *result)
{
	char	*try_path;
	char	*join_path;

	join_path = NULL;
	while (*paths)
	{
		try_path = get_next_path(&paths);
		join_path = x_ft_strjoin(try_path, arg);
		ft_free(&try_path);
		if (judge(join_path, result))
			break ;
		ft_free(&join_path);
	}
	return (join_path);
}

char	*create_accessible_path(char *paths, \
								const char *const command, \
								t_result *result)
{
	return (create_valid_path_by_judge(\
					paths, command, is_accessible_command, result));
}

char	*create_executable_path(char *paths, \
								const char *const command, \
								t_result *result)
{
	return (create_valid_path_by_judge(\
					paths, command, is_executable_command, result));
}
