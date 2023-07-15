#include <fcntl.h>
#include <stdio.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ft_mem.h"

static int	open_file_dup_errno(const char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, OPEN_PERMISSION);
	if (fd == OPEN_ERROR)
	{
		perror("open");
		return (PROCESS_ERROR);
	}
	return (fd);
}

t_result	create_filename_and_open_heredoc_fd(int *fd, char **filename)
{
	*filename = create_heredoc_filename();
	if (!*filename)
		return (PROCESS_ERROR);
	*fd = open_file_dup_errno(*filename);
	if (*fd == OPEN_ERROR)
	{
		ft_free(filename);
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
