#include <fcntl.h>
#include <stdio.h>
#include "ms_parse.h"
#include "ft_sys.h"

static int	open_file_dup_errno(const char *file, int *tmp_err)
{
	int	fd;

	errno = 0;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	*tmp_err = errno;
	return (fd);
}

t_result	create_filename_and_open_heredoc_fd(int *fd, char **filename)
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
