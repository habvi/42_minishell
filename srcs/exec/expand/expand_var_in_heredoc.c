#include <fcntl.h>
#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

static t_result	expand_and_transfer_heredoc(int raw_fd, \
											int expand_fd, \
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
		line = ft_get_next_line(raw_fd, &result);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (!line)
			break ;
		expand_line = get_expand_token_str(line, context);
		ft_dprintf(expand_fd, expand_line);
		ft_free(&line);
		ft_free(&expand_line);
	}
	return (result);
}

static t_result	open_heredoc_fds(int *raw_fd, \
									int *expand_fd, \
									const char *raw_filename, \
									char **new_filename)
{
	t_result	result;

	*raw_fd = x_open(raw_filename, O_RDONLY);
	if (*raw_fd == OPEN_ERROR)
		return (PROCESS_ERROR);
	result = create_filename_and_open_heredoc_fd(expand_fd, new_filename);
	return (result);
}

// todo: close(fd) fail, unlink(file)...?
static t_result	clear_expand_in_heredoc(int raw_fd, \
										int expand_fd, \
										char **filename, \
										char **new_filename)
{
	if (x_close(raw_fd) == CLOSE_ERROR)
	{
		x_close(expand_fd);
		x_unlink(*new_filename);
		return (PROCESS_ERROR);
	}
	if (x_close(expand_fd) == CLOSE_ERROR)
	{
		ft_free(new_filename);
		return (PROCESS_ERROR);
	}
	if (x_unlink(*filename) == UNLINK_ERROR)
	{
		ft_free(new_filename);
		return (PROCESS_ERROR);
	}
	ft_free(filename);
	return (SUCCESS);
}

t_result	expand_variables_in_heredoc(t_redirect *redirect, \
										t_context *context)
{
	int			raw_fd;
	int			expand_fd;
	char		*new_filename;
	t_result	result;

	result = open_heredoc_fds(&raw_fd, \
								&expand_fd, \
								redirect->heredoc_filename, \
								&new_filename);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	result = expand_and_transfer_heredoc(raw_fd, expand_fd, context);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	result = clear_expand_in_heredoc(raw_fd, \
										expand_fd, \
										&redirect->heredoc_filename, \
										&new_filename);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	redirect->heredoc_filename = new_filename;
	return (result);
}
