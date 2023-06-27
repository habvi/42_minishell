#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "minishell.h"
#include "ft_mem.h"
#include "ft_dprintf.h"
#include "ft_sys.h"

static char	*get_current_path(int *err)
{
	char	*path;
	size_t	size;

	size = PATH_MAX;
	path = (char *)x_malloc(sizeof(char) * size);
	if (!path)
		ft_abort();
	*err = 0;
	while (true)
	{
		errno = 0;
		getcwd(path, size);
		*err = errno;
		if (*err != ERANGE)
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
		cwd = ft_free(&cwd);
	if (err)
		*err = tmp_err;
	if (!cwd)
	{
		ft_dprintf(STDERR_FILENO, \
		"%s: %s: %s: %s\n", \
		for_whom, ERROR_MSG_RETRIEVE_CWD, ERROR_MSG_GETCWD, strerror(tmp_err));
	}
	return (cwd);
}
