#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

void	*ast_print_error(t_deque_node *token_node)
{
	t_token	*token;
	char	*err_arg;

	if (!token_node)
		err_arg = SYNTAX_DEFAULT_ARG;
	else
	{
		token = (t_token *)token_node->content;
		err_arg = token->str;
	}
	puterr_msg_quoted_arg(ERROR_MSG_SYNTAX, err_arg);
	return (NULL);
}

void	*set_error_status(uint8_t *status)
{
	*status = SYNTAX_ERROR;
	return (NULL);
}

void	set_error_status_and_result(t_context *context, t_result *result)
{
	context->status = SYNTAX_ERROR;
	*result = FAILURE;
}
