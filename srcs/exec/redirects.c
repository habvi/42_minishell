#include <fcntl.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

#define OPEN_FLAG_READ		(O_RDONLY)
#define OPEN_FLAG_WRITE		(O_CREAT | O_WRONLY | O_TRUNC)
#define OPEN_FLAG_APPEND	(O_CREAT | O_WRONLY | O_APPEND)

static t_result	connect_process_io_fd(const char *path, int *fd, int open_flag)
{
	int	open_fd;

	if (open_flag == OPEN_FLAG_READ)
	{
		open_fd = open(path, open_flag); // todo: error
		if (*fd != IN_FD_INIT)
			close(*fd); // todo: error
		*fd = open_fd;
	}
	else if (open_flag == OPEN_FLAG_WRITE || open_flag == OPEN_FLAG_APPEND)
	{
		open_fd = open(path, open_flag, 0664); // todo: error
		if (*fd != OUT_FD_INIT)
			close(*fd); // todo: error
		*fd = open_fd;
	}
	return (SUCCESS);
}

static t_result	redirect_token(t_redirect *redirect, int proc_fd[2])
{
	t_result		result;
	const t_token	*token = redirect->tokens->node->content;

	if (redirect->kind == TOKEN_KIND_REDIRECT_IN)
		result = connect_process_io_fd(token->str, &proc_fd[IN], OPEN_FLAG_READ);
	else if (redirect->kind == TOKEN_KIND_REDIRECT_OUT)
		result = connect_process_io_fd(token->str, &proc_fd[OUT], OPEN_FLAG_WRITE);
	else if (redirect->kind == TOKEN_KIND_REDIRECT_APPEND)
		result = connect_process_io_fd(token->str, &proc_fd[OUT], OPEN_FLAG_APPEND);
	else
		result = connect_process_io_fd(redirect->heredoc_filename, &proc_fd[IN], OPEN_FLAG_READ);
	return (result);
}

static bool	is_ambiguous_redirect(t_redirect *redirect)
{
	if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
		return (false);
	return (redirect->tokens->size != 1);
}

static t_result	exec_redirect(t_redirect *redirect, int proc_fd[2])
{
	t_result	result;

	if (is_ambiguous_redirect(redirect))
	{
		ft_dprintf(2, "error: ambiguous redirect\n");
		return (FAILURE);
	}
	result = redirect_token(redirect, proc_fd);
	return (result);
}

// OK [redirect_symbol]-[file]
// NG [redirect_symbol]-[redirect_symbol]: dropped $var
//    [redirect_symbol]-[file]-[file]    : splitted $var
t_result	redirect_fd(t_ast *self_node, t_context *context)
{
	t_deque_node	*node;
	t_result		result;

	if (!self_node->redirect_list)
		return (SUCCESS); //todo
	node = self_node->redirect_list->node;
	while (node)
	{
		result = exec_redirect(node->content, self_node->proc_fd);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		if (result == FAILURE)
			context->status = 1;
		node = node->next;
	}
	return (SUCCESS);
}
