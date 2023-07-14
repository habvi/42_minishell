#include <fcntl.h>
#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_mem.h"

static t_quote	get_token_head_quote_kind(t_deque *tokens)
{
	t_token	*token;

	token = (t_token *)tokens->node->content;
	return (token->quote);
}

static t_result	expand_and_transfer_heredoc(int raw_fd, int expand_fd, t_context *context)
{
	char	*line;
	char	*expand_line;

	line = NULL;
	expand_line = NULL;
	while (true)
	{
		(void)raw_fd;
//		line = get_next_line(raw_fd);
		if (!line)
			break ;
		expand_line = get_expand_token_str(line, context);
		ft_dprintf(expand_fd, expand_line);
		ft_free(&line);
		ft_free(&expand_line);
	}
	return (SUCCESS);
}

static t_result	expand_variables_in_heredoc(t_redirect *redirect, t_context *context)
{
	int			raw_fd;
	int			expand_fd;
	char		*new_filename;
	t_result	result;

	// open
	raw_fd = open(redirect->heredoc_filename, O_RDONLY);
	if 	(raw_fd == OPEN_ERROR)
		return (PROCESS_ERROR); // todo: error?
	result = open_heredoc_fd(&expand_fd, &new_filename); // todo: func name create_
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR); // todo: error?

	// expand: read from before_fd -> expand -> write to after_fd
	result = expand_and_transfer_heredoc(raw_fd, expand_fd, context);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR); // todo: error?

	// close
	close(raw_fd); // todo: error
	close(expand_fd); // todo: error

	// replace before->after
	unlink(redirect->heredoc_filename); // todo: error
	ft_free(&redirect->heredoc_filename);
	redirect->heredoc_filename = new_filename;
	return (SUCCESS);
}

t_result	expand_for_heredoc(t_redirect *redirect, t_context *context)
{
	if (get_token_head_quote_kind(redirect->tokens) != QUOTE_NONE)
		return (SUCCESS);
	return (expand_variables_in_heredoc(redirect, context));
}