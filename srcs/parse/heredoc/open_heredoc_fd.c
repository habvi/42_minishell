#include <fcntl.h>
#include <stdio.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ft_dprintf.h"
#include "ft_sys.h"
#include "ft_mem.h"

static int	open_file_dup_errno(const char *file, int *tmp_err)
{
	int	fd;

	errno = 0;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, OPEN_PERMISSION);
	*tmp_err = errno;
	return (fd);
}

t_result	open_heredoc_fd(int *fd, char **filename)
{
	int	tmp_err;

	*filename = create_heredoc_filename();
	if (!*filename)
		return (PROCESS_ERROR);
	*fd = open_file_dup_errno(*filename, &tmp_err);
	if (tmp_err == ENOMEM)
	{
		perror("open"); // todo: msg
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
