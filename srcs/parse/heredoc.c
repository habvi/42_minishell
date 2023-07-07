#include <fcntl.h>
#include <limits.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"
#include "ft_lib.h"
#include "ft_string.h"
#include "ft_sys.h"
#include "ft_mem.h"

static void	execute_heredoc_each(int fd, const char *delimiter)
{
	char	*line;

	rl_outstream = stderr;
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s (wanted `%s')", \
			SHELL_NAME, ERROR_TYPE_WARNING, ERROR_MSG_HEREDOC_EOF, delimiter); // todo: wanted
			break ;
		}
		if (ft_streq(line, delimiter))
		{
			ft_free(&line);
			break ;
		}
		ft_dprintf(fd, line);
		ft_dprintf(fd, "\n");
		ft_free(&line);
	}
}

static char	*get_heredoc_eof(t_deque_node *token_node)
{
	t_token	*token;

	token = (t_token *)token_node->content;
	return (token->str);
}

// todo: check filename
static t_result	execute_heredoc_all(t_redirect *redirect)
{
	t_deque_node	*token_node;
	int				in_fd;
	char			*filename;
	char 			*delimiter;
	t_result		result;

	if (!redirect)
		return (SUCCESS);
	token_node = redirect->list->node;
	in_fd = IN_FD_INIT;
	filename = NULL;
	while (token_node)
	{
		if (!is_token_kind_redirection_from_node(token_node))
		{
			token_node = token_node->next;
			continue ;
		}
		result = open_heredoc_filedes(&in_fd, &filename);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		delimiter = get_heredoc_eof(token_node->next);
		execute_heredoc_each(in_fd, delimiter);
		token_node = token_node->next;
	}
	redirect->in_fd = in_fd;
	redirect->heredoc_filename = filename;
	return (SUCCESS);
}

t_result	execute_heredoc(t_ast *ast_node)
{
	move_redirect_from_command(ast_node);
	if (execute_heredoc_all(ast_node->redirects) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
