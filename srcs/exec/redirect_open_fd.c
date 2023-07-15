#include <fcntl.h>
#include <string.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_sys.h"

// todo: error, macro
static int	open_redirect_fd(const char *path, \
								t_open_flag open_flag, \
								int *tmp_err)
{
	int	open_fd;

	errno = 0;
	if (open_flag == OPEN_FOR_IN)
		open_fd = open(path, open_flag);
	else
		open_fd = open(path, open_flag, OPEN_PERMISSION);
	*tmp_err = errno;
	return (open_fd);
}

static t_result	close_proc_in_fd(int proc_in_fd)
{
	if (proc_in_fd == IN_FD_INIT)
		return (SUCCESS);
	if (x_close(proc_in_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	close_proc_out_fd(int proc_out_fd)
{
	if (proc_out_fd == OUT_FD_INIT)
		return (SUCCESS);
	if (x_close(proc_out_fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

static t_result	connect_proc_io_fd(const char *path, \
									int *proc_fd, \
									t_open_flag open_flag)
{
	int	open_fd;
	int	open_errno;

	open_fd = open_redirect_fd(path, open_flag, &open_errno);
	if (open_fd == OPEN_ERROR)
	{
		ft_dprintf(2, "%s: %s: %s\n", SHELL_NAME, path, strerror(open_errno));
		return (FAILURE);
	}
	if (open_flag == OPEN_FOR_IN)
	{
		if (close_proc_in_fd(*proc_fd) == CLOSE_ERROR)
			return (PROCESS_ERROR);
	}
	else
	{
		if (close_proc_out_fd(*proc_fd) == CLOSE_ERROR)
			return (PROCESS_ERROR);
	}
	*proc_fd = open_fd;
	return (SUCCESS);
}

t_result	open_redirect_fd_and_save_to_proc(t_redirect *redirect, \
												int proc_fd[2])
{
	const t_token	*token = redirect->tokens->node->content;
	t_result		result;
	char			*path;

	path = token->str;
	if (redirect->kind == TOKEN_KIND_REDIRECT_IN)
		result = connect_proc_io_fd(path, &proc_fd[IN], OPEN_FOR_IN);
	else if (redirect->kind == TOKEN_KIND_REDIRECT_OUT)
		result = connect_proc_io_fd(path, &proc_fd[OUT], OPEN_FOR_OUT);
	else if (redirect->kind == TOKEN_KIND_REDIRECT_APPEND)
		result = connect_proc_io_fd(token->str, &proc_fd[OUT], OPEN_FOR_APPEND);
	else
	{
		path = redirect->heredoc_filename;
		result = connect_proc_io_fd(path, &proc_fd[IN], OPEN_FOR_IN);
	}
	if (result == FAILURE)
	{
		close_proc_in_fd(proc_fd[IN]); // todo: error
		close_proc_out_fd(proc_fd[OUT]); // todo: error
	}
	return (result);
}
