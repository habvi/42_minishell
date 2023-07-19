#include <fcntl.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_sys.h"
#include "ft_string.h"

static int	open_redirect_fd(const char *path, \
								t_open_flag open_flag, \
								int *tmp_err)
{
	int	open_fd;

	errno = 0;
	*tmp_err = 0;
	if (ft_streq(path, DEV_STDIN_PATH))
		return (STDIN_FILENO);
	if (ft_streq(path, DEV_STDOUT_PATH))
		return (STDOUT_FILENO);
	if (open_flag == OPEN_FOR_IN)
		open_fd = open(path, open_flag);
	else
		open_fd = open(path, open_flag, OPEN_PERMISSION);
	*tmp_err = errno;
	return (open_fd);
}

static bool	is_open_failure(int open_errno)
{
	return (open_errno == EACCES || open_errno == EISDIR \
	|| open_errno == ELOOP || open_errno == ENAMETOOLONG \
	|| open_errno == ENODEV || open_errno == ENOENT \
	|| open_errno == ENOTDIR || open_errno == ENXIO \
	|| open_errno == EOVERFLOW || open_errno == EROFS \
	|| open_errno == ETXTBSY || open_errno == ETXTBSY);
}

static t_result	connect_proc_io_fd(const char *path, \
									int *proc_fd, \
									t_open_flag open_flag, \
									int *open_errno)
{
	int	open_fd;

	if (open_flag == OPEN_FOR_IN)
	{
		if (close_proc_in_fd(proc_fd) == CLOSE_ERROR)
			return (PROCESS_ERROR);
	}
	else
	{
		if (close_proc_out_fd(proc_fd) == CLOSE_ERROR)
			return (PROCESS_ERROR);
	}
	open_fd = open_redirect_fd(path, open_flag, open_errno);
	if (open_fd == OPEN_ERROR)
	{
		if (is_open_failure(*open_errno))
			return (FAILURE);
		return (PROCESS_ERROR);
	}
	*proc_fd = open_fd;
	return (SUCCESS);
}

t_result	open_redirect_fd_and_save_to_proc(t_redirect *redirect, \
												int proc_fd[2], \
												int *err)
{
	const t_token	*token = redirect->tokens->node->content;
	t_result		result;
	char			*path;

	path = token->str;
	if (redirect->kind == TOKEN_KIND_REDIRECT_IN)
		result = connect_proc_io_fd(path, &proc_fd[IN], OPEN_FOR_IN, err);
	else if (redirect->kind == TOKEN_KIND_REDIRECT_OUT)
		result = connect_proc_io_fd(path, &proc_fd[OUT], OPEN_FOR_OUT, err);
	else if (redirect->kind == TOKEN_KIND_REDIRECT_APPEND)
		result = connect_proc_io_fd(path, &proc_fd[OUT], OPEN_FOR_APPEND, err);
	else
	{
		path = redirect->heredoc_filename;
		result = connect_proc_io_fd(path, &proc_fd[IN], OPEN_FOR_IN, err);
	}
	if (result != SUCCESS)
	{
		if (close_proc_in_fd(&proc_fd[IN]) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (close_proc_out_fd(&proc_fd[OUT]) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (result);
}
