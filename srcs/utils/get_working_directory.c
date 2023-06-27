#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "minishell.h"
#include "ft_dprintf.h"
#include "ft_mem.h"
#include "ft_sys.h"

// use getcwd to original error handling.
static char	*get_current_path(int *tmp_err)
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
		path = (char *)ft_realloc(path, size);
		if (!path)
			ft_abort();
	}
	return (path);
}

/* ref: get_working_directory() in bash/builtins/common.c L623 */
char	*get_working_directory(char *for_whom)
{
	char	*cwd;
	int		tmp_err;

	cwd = get_current_path(&tmp_err);
	if (tmp_err)
	{
		ft_dprintf(STDERR_FILENO, \
		"%s: %s: %s: %s\n", \
		for_whom, ERROR_MSG_RETRIEVE_CWD, ERROR_MSG_GETCWD, strerror(tmp_err));
		ft_free(&cwd);
		return (NULL);
	}
	return (cwd);
}
