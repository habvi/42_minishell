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

static void	clean_up_prev_heredoc(int in_fd, char *filename)
{
	close(in_fd); 		// todo: error handling
	unlink(filename);	// todo: error handling
	ft_free(&filename);
}

// todo: error handling and msg
static t_result	open_heredoc_filedes(int *in_fd, char **filename)
{
	int	tmp_err;

	if (*in_fd != IN_FD_INIT)
		clean_up_prev_heredoc(*in_fd, *filename);
	*filename = create_heredoc_filename();
	errno = 0;
	*in_fd = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
//	ft_dprintf(2, "new in_fd:%d, filename:%s\n", *in_fd, *filename);
	tmp_err = errno;
	if (tmp_err == ENOMEM)
	{
		perror("open");
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

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
