#include <fcntl.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ft_dprintf.h"
#include "ft_sys.h"
#include "ft_mem.h"

// todo: error handling
static void	clean_up_prev_heredoc(int in_fd, char *filename)
{
	close(in_fd);
	unlink(filename);
	ft_free(&filename);
}

static int	open_file_dup_errno(const char *file, int *tmp_err)
{
	int	fd;

	errno = 0;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, OPEN_PERMISSION);
	*tmp_err = errno;
	return (fd);
}

static bool	is_prev_heredoc_file_exist(int in_fd)
{
	return (in_fd != IN_FD_INIT);
}

t_result	open_heredoc_filedes(int *in_fd, char **filename)
{
	int	tmp_err;

	if (is_prev_heredoc_file_exist(*in_fd))
		clean_up_prev_heredoc(*in_fd, *filename);
	*filename = create_heredoc_filename();
	if (!*filename)
		return (PROCESS_ERROR);
	*in_fd = open_file_dup_errno(*filename, &tmp_err);
	if (tmp_err == ENOMEM)
	{
		perror("open"); // todo: msg
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
