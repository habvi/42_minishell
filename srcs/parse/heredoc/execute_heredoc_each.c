#include <readline/readline.h>
#include "minishell.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

static void	read_input_save_to_fd(int fd, const char *delimiter)
{
	char	*line;

	rl_outstream = stderr;
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
		{
			puterr_heredoc_wanted_eof(delimiter);
			break ;
		}
		if (ft_streq(line, delimiter))
		{
			ft_free(&line);
			break ;
		}
		ft_dprintf(fd, "%s\n", line);
		ft_free(&line);
	}
}

static bool	is_quote_token_exist(const t_deque *tokens)
{
	bool			has_quote;
	t_deque_node	*token_node;
	t_token			*token;

	has_quote = false;
	token_node = tokens->node;
	while (token_node)
	{
		token = (t_token *)token_node->content;
		if (token->quote != QUOTE_NONE)
		{
			has_quote = true;
			break ;
		}
		token_node = token_node->next;
	}
	return (has_quote);
}

// concat tokens
// at least quoted in tokens,
// assign quote flag for determination of expand variable
static void	create_heredoc_delimiter(t_deque *tokens)
{
	bool	is_quoted;
	t_token	*token;

	is_quoted = is_quote_token_exist(tokens);
	concat_tokens(tokens);
	token = (t_token *)tokens->node->content;
	if (is_quoted)
		token->quote = QUOTE_DOUBLE; // include quote single
	else
		token->quote = QUOTE_NONE;
}

t_result	execute_heredoc_each(t_redirect *redirect)
{
	t_token			*token;
	char			*delimiter;
	int				fd;

	if (create_filename_and_open_heredoc_fd(\
		&fd, &redirect->heredoc_filename) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	create_heredoc_delimiter(redirect->tokens);
	token = redirect->tokens->node->content;
	delimiter = token->str; // don't free
	read_input_save_to_fd(fd, delimiter);
	if (x_close(fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
