#include <errno.h>
#include "minishell.h"
#include "ms_exec.h"
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

char	*create_executable_or_accessible_path(char *paths, \
												const char *const command, \
												bool (*judge)(const char *path))
{
	char	*try_path;
	char	*ret_path;

	ret_path = NULL;
	while (*paths)
	{
		try_path = get_next_path(&paths);
		ret_path = x_ft_strjoin(try_path, command);
		ft_free(&try_path);
		if (judge(ret_path))
			break ;
		ft_free(&ret_path);
	}
	return (ret_path);
}

char	*create_accessible_path(char *paths, const char *const command)
{
	return (create_executable_or_accessible_path(paths, \
													command, \
													is_accessible_command));
}

char	*create_executable_path(char *paths, const char *const command)
{
	return (create_executable_or_accessible_path(paths, \
													command, \
													is_executable_command));
}
