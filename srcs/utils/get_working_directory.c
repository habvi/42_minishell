#include <limits.h>
#include <string.h>
#include "minishell.h"
#include "ft_mem.h"
#include "ft_sys.h"

static char	*extend_path(char **path, const size_t newsize)
{
	char	*new_path;

	new_path = (char *)x_malloc(sizeof(char) * newsize);
	if (!new_path)
		ft_abort();
	ft_free((void **)path);
	return (new_path);
}

// use getcwd to original error handling.
// check tmp_err. can't judge !cwd.
char	*get_current_path(int *tmp_err)
{
	char	*path;
	size_t	size;

	size = PATH_MAX;
	path = (char *)x_malloc(sizeof(char) * size);
	if (!path)
		ft_abort();
	*tmp_err = 0;
	while (true)
	{
		errno = 0;
		getcwd(path, size);
		*tmp_err = errno;
		if (*tmp_err != ERANGE)
			break ;
		size *= 2;
		path = extend_path(&path, size);
	}
	return (path);
}

bool	is_getcwd_failure(const int tmp_err)
{
	return (tmp_err == EACCES || tmp_err == ENAMETOOLONG || tmp_err == ENOENT);
}

/* ref: get_working_directory() in bash/builtins/common.c L623 */
char	*get_working_directory(const char *for_whom, t_result *result)
{
	char	*cwd;
	int		tmp_err;

	cwd = get_current_path(&tmp_err);
	if (tmp_err)
	{
		ft_free((void **)&cwd);
		if (is_getcwd_failure(tmp_err))
		{
			puterr_whom_cmd_arg_msg(for_whom, \
									ERROR_MSG_RETRIEVE_CWD, \
									ERROR_MSG_GETCWD, \
									strerror(tmp_err));
			*result = FAILURE;
			return (NULL);
		}
		ft_dprintf(STDERR_FILENO, "%s\n", strerror(tmp_err));
		*result = PROCESS_ERROR;
		return (NULL);
	}
	*result = SUCCESS;
	return (cwd);
}
