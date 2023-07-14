#include <fcntl.h>
#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_gnl.h"
#include "ft_mem.h"

static bool	is_expand_in_heredoc(t_redirect *redirect)
{
	t_token	*token;

	token = (t_token *)redirect->tokens->node->content;
	return (token->quote == QUOTE_NONE);
}

static t_result	expand_and_transfer_heredoc(int raw_fd, \
											int expand_fd, \
											t_context *context)
{
	char	*line;
	char	*expand_line;

	line = NULL;
	expand_line = NULL;
	while (true)
	{
		(void)raw_fd;
		line = get_next_line(raw_fd);
		if (!line)
			break ;
		expand_line = get_expand_token_str(line, context);
		ft_dprintf(expand_fd, expand_line);
		ft_free(&line);
		ft_free(&expand_line);
	}
	return (SUCCESS);
}

static t_result	expand_variables_in_heredoc(t_redirect *redirect, \
											t_context *context)
{
	int			raw_fd;
	int			expand_fd;
	char		*new_filename;
	t_result	result;

	raw_fd = open(redirect->heredoc_filename, O_RDONLY);
	if (raw_fd == OPEN_ERROR)
		return (PROCESS_ERROR); // todo: error?
	result = create_filename_and_open_heredoc_fd(&expand_fd, &new_filename);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR); // todo: error?
	result = expand_and_transfer_heredoc(raw_fd, expand_fd, context);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR); // todo: error?
	close(raw_fd); // todo: error
	close(expand_fd); // todo: error
	unlink(redirect->heredoc_filename); // todo: error
	ft_free(&redirect->heredoc_filename);
	redirect->heredoc_filename = new_filename;
	return (SUCCESS);
}

// redirect->kind is NODE_KIND_HEREDOC
t_result	expand_for_heredoc(t_redirect *redirect, t_context *context)
{
	if (!is_expand_in_heredoc(redirect))
		return (SUCCESS);
	return (expand_variables_in_heredoc(redirect, context));
}
