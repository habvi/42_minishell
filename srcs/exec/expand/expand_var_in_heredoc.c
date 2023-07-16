#include <fcntl.h>
#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

static t_result	expand_and_transfer_heredoc(int old_fd, \
											int new_fd, \
											t_context *context)
{
	char		*line;
	char		*expand_line;
	t_result	result;

	line = NULL;
	expand_line = NULL;
	result = SUCCESS;
	while (true)
	{
		line = ft_get_next_line(old_fd, &result);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (!line)
			break ;
		expand_line = get_expand_token_str(line, context);
		ft_dprintf(new_fd, expand_line);
		ft_free(&line);
		ft_free(&expand_line);
	}
	return (result);
}

static t_result	open_heredoc_fds(int *old_fd, \
									int *new_fd, \
									const char *old_filename, \
									char **new_filename)
{
	t_result	result;

	*old_fd = x_open(old_filename, O_RDONLY);
	if (*old_fd == OPEN_ERROR)
		return (PROCESS_ERROR);
	result = create_filename_and_open_heredoc_fd(new_fd, new_filename);
	return (result);
}

static t_result	clear_expand_in_heredoc(int old_fd, \
										int new_fd, \
										char **old_filename, \
										char **new_filename)
{
	if (x_close(old_fd) == CLOSE_ERROR)
	{
		x_close(new_fd);
		x_unlink(*new_filename);
		ft_free(new_filename);
		return (PROCESS_ERROR);
	}
	if (x_close(new_fd) == CLOSE_ERROR)
	{
		x_unlink(*new_filename);
		ft_free(new_filename);
		return (PROCESS_ERROR);
	}
	if (x_unlink(*old_filename) == UNLINK_ERROR)
	{
		x_unlink(*new_filename);
		ft_free(new_filename);
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

static void	clear_fd_for_error(int old_fd, int new_fd, char **new_filename)
{
	x_close(old_fd);
	x_close(new_fd);
	x_unlink(*new_filename);
	ft_free(new_filename);
}

t_result	expand_variables_in_heredoc(t_redirect *redirect, \
										t_context *context)
{
	int			old_fd;
	int			new_fd;
	char		*new_filename;
	char		*old_filename;

	old_filename = redirect->heredoc_filename;
	if (open_heredoc_fds(\
		&old_fd, &new_fd, old_filename, &new_filename) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (expand_and_transfer_heredoc(old_fd, new_fd, context) == PROCESS_ERROR)
	{
		clear_fd_for_error(old_fd, new_fd, &new_filename);
		return (PROCESS_ERROR);
	}
	if (clear_expand_in_heredoc(\
		old_fd, new_fd, &old_filename, &new_filename) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	ft_free(&redirect->heredoc_filename);
	redirect->heredoc_filename = new_filename;
	return (SUCCESS);
}
