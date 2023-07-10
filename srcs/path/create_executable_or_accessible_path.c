#include <errno.h>
#include "minishell.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_mem.h"

static bool	is_accessible_command(const char *path)
{
	int	ret;

	errno = 0;
	ret = access(path, X_OK); // todo: x?
	if (ret != ACCESS_ERROR)
		return (true);
	if (errno == EACCES)
		return (true);
	return (false);
}

static bool	is_executable_command(const char *path)
{
	return (access(path, X_OK) != ACCESS_ERROR);
}

char	*create_valid_path_by_judge(char *paths, \
									const char *const arg, \
									bool (*judge)(const char *path))
{
	char	*try_path;
	char	*join_path;

	join_path = NULL;
	while (*paths)
	{
		try_path = get_next_path(&paths);
		join_path = x_ft_strjoin(try_path, arg);
		ft_free(&try_path);
		if (judge(join_path))
			break ;
		ft_free(&join_path);
	}
	return (join_path);
}

char	*create_accessible_path(char *paths, const char *const command)
{
	return (create_valid_path_by_judge(paths, command, is_accessible_command));
}

char	*create_executable_path(char *paths, const char *const command)
{
	return (create_valid_path_by_judge(paths, command, is_executable_command));
}
