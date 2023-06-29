#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"
#include "ft_mem.h"

bool	is_absolute_path(const char *path)
{
	return (path[0] == ABSOLUTE_PATH_HEAD);
}

static t_result	exec_chdir(const char *path, uint8_t *status)
{
	if (chdir(path) == CHDIR_ERROR)
	{
		*status = 1; // todo
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

static bool	is_tail_slash(const char *path)
{
	const size_t	size = ft_strlen(path);

	if (!path)
		return (false);
	return (path[size - 1] == '/');
}

// make absolute_path
char	*join_pwd_and_relative(const char *pwd, const char *relative_path)
{
	char	*tmp;
	char	*absolute_path;

	if (is_tail_slash(pwd))
	{
		absolute_path = ft_strjoin(pwd, relative_path);
		if (!absolute_path)
			ft_abort();
	}
	else
	{
		tmp = ft_strjoin(pwd, "/");
		if (!tmp)
			ft_abort();
		absolute_path = ft_strjoin(tmp, relative_path);
		if (!absolute_path)
			ft_abort();
	}
	return (absolute_path);
}

// if chdir error, no need for auto perror.
// "pwd + path" -> "path"
t_result	cd_change_dir_to_valid_path(const char *path, \
										const char *pwd, \
										uint8_t *status)
{
	const char	*relative_path = path;
	char		*absolute_path;

	if (is_absolute_path(path))
	{
		if (exec_chdir(path, status) == SUCCESS)
			return (SUCCESS);
	}
	else
	{
		relative_path = path;
		absolute_path = join_pwd_and_relative(pwd, relative_path);
		if (exec_chdir(absolute_path, status) == SUCCESS)
		{
			ft_free(&absolute_path);
			return (SUCCESS);
		}
		ft_free(&absolute_path);
		if (exec_chdir(relative_path, status) == SUCCESS)
			return (SUCCESS);
	}
	return (FAILURE);
}
