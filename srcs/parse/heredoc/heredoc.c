#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_expansion.h"
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

static bool	is_quote_token_exist(t_deque *tokens)
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

static t_result	execute_heredoc_each(t_redirect *redirect)
{
	t_result		result;
	t_token			*token;
	char			*delimiter;
	int				fd;

	result = open_heredoc_fd(&fd, &redirect->heredoc_filename);
	if (result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	create_heredoc_delimiter(redirect->tokens);
	token = redirect->tokens->node->content;
	delimiter = token->str; // don't free
	read_input_save_to_fd(fd, delimiter);
	close(fd); //todo:error
	return (SUCCESS);
}

static t_result	execute_heredoc_all(t_deque *redirect_list)
{
	t_deque_node	*redirect_node;
	t_result		result;
	t_redirect		*redirect;

	if (!redirect_list)
		return (SUCCESS);
	redirect_node = redirect_list->node;
	while (redirect_node)
	{
		redirect = (t_redirect *)redirect_node->content;
		if (redirect->kind != TOKEN_KIND_REDIRECT_HEREDOC)
		{
			redirect_node = redirect_node->next;
			continue ;
		}
		result = execute_heredoc_each(redirect);
		if (result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		redirect_node = redirect_node->next;
	}
	return (SUCCESS);
}

t_result	execute_heredoc(t_ast *ast_node)
{
	t_result	heredoc_result;
	t_result	left_result;
	t_result	right_result;

	if (!ast_node)
		return (SUCCESS);
	left_result = execute_heredoc(ast_node->left);
	if (left_result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	right_result = execute_heredoc(ast_node->right);
	if (right_result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	if (!is_node_kind_exec_heredoc(ast_node->kind))
		return (SUCCESS);
	move_redirect_from_command(ast_node);
	heredoc_result = execute_heredoc_all(ast_node->redirect_list);
	if (heredoc_result == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
