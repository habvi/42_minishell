#include <fcntl.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

#define OPEN_FLAG_READ	O_RDONLY
#define OPEN_FLAG_WRITE	O_WRONLY

// todo: tmp. append, heredoc
static t_result	connect_process_io_fd(t_redirect *redirects, \
										const char *path, \
										int open_flag)
{
	int	fd;

	fd = open(path, open_flag);
	if (fd == -1)
		return (PROCESS_ERROR); //todo
	if (open_flag == OPEN_FLAG_READ)
	{
		close(redirects->in_fd);
		redirects->in_fd = fd;
	}
	else if (open_flag == OPEN_FLAG_WRITE)
	{
		close(redirects->out_fd);
		redirects->out_fd = fd;
	}
	return (SUCCESS);
}

static t_result	redirect_token(t_redirect *redirects, \
								t_token_kind kind, \
								const char *path)
{
	t_result	result;

	if (kind == TOKEN_KIND_REDIRECT_IN || kind == TOKEN_KIND_REDIRECT_HEREDOC)
		result = connect_process_io_fd(redirects, path, OPEN_FLAG_READ);
	else if (kind == TOKEN_KIND_REDIRECT_OUT \
			|| kind == TOKEN_KIND_REDIRECT_APPEND)
		result = connect_process_io_fd(redirects, path, OPEN_FLAG_WRITE);
	return (result);
}

t_result	redirect_fd(t_redirect *redirects, t_context *context)
{
	t_deque_node	*node;
	t_token			*token;
	char			*path;

	if (!redirects)
		return (SUCCESS); //todo
	node = redirects->list->node;
	while (node)
	{
		token = (t_token *)node->content;
		if (!is_token_kind_redirection(token->kind))
		{
			context->status = 1; // todo
			return (FAILURE); // todo: error
		}
		if (!node->next)
		{
			context->status = 1; // todo
			return (FAILURE); // todo: ambiguous redirect error?
		}
		token = (t_token *)node->next->content;
		path = token->str;
		redirect_token(redirects, token->kind, path);
		node = node->next;
	}
	return (SUCCESS);
}
