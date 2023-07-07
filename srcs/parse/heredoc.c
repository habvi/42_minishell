#include <fcntl.h>
#include <limits.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"
#include "ft_string.h"
#include "ft_mem.h"

// todo: wanted in warning msg
static void	read_input_save_to_fd(int fd, const char *delimiter)
{
	char	*line;

	rl_outstream = stderr;
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s (wanted `%s')\n", \
			SHELL_NAME, ERROR_TYPE_WARNING, ERROR_MSG_HEREDOC_EOF, delimiter);
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

static char	*get_heredoc_delimiter(t_deque_node *token_node)
{
	t_token	*token;

	token = (t_token *)token_node->content;
	return (token->str);
}

static t_result	execute_heredoc_each(t_deque_node *token_node, \
										int *in_fd, \
										char **filename)
{
	t_result	result;
	char		*delimiter;

	if (!is_token_kind_redirection_from_node(token_node))
		return (CONTINUE);
	result = open_heredoc_filedes(in_fd, filename); // todo change fd...
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	delimiter = get_heredoc_delimiter(token_node->next); // don't free
	read_input_save_to_fd(*in_fd, delimiter);
	return (SUCCESS);
}

static t_result	execute_heredoc_all(t_redirect *redirect)
{
	t_deque_node	*token_node;
	int				in_fd;
	char			*filename;
	t_result		result;

	if (!redirect)
		return (SUCCESS);
	token_node = redirect->list->node;
	in_fd = IN_FD_INIT;
	filename = NULL;
	while (token_node)
	{
		result = execute_heredoc_each(token_node, &in_fd, &filename);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		token_node = token_node->next;
	}
	redirect->in_fd = in_fd;
	redirect->heredoc_filename = filename;
	return (SUCCESS);
}

t_result	execute_heredoc(t_ast *ast_node)
{
	t_result	heredoc_result;

	move_redirect_from_command(ast_node);
	heredoc_result = execute_heredoc_all(ast_node->redirects);
	if (heredoc_result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
