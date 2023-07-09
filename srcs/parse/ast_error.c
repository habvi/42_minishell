#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

void	*ast_print_error(t_deque_node *token_node)
{
	t_token	*token;
	char	*err_arg;

	if (!token_node)
		err_arg = ERROR_SYNTAX_DEFAULT_ARG;
	else
	{
		token = (t_token *)token_node->content;
		err_arg = token->str;
	}
	ft_dprintf(STDERR_FILENO, "%s: %s `%s'\n", \
				SHELL_NAME, ERROR_MSG_SYNTAX, err_arg);
	return (NULL);
}

void	set_error_status(t_context *context, t_result *result)
{
	context->status = SYNTAX_ERROR;
	*result = FAILURE;
}
