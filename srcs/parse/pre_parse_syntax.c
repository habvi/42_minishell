#include "minishell.h"
#include "ms_parse.h"
#include "ft_deque.h"

static char	*get_syntax_error_arg(const t_deque_node *node)
{
	t_token	*token;

	if (!node)
		return (SYNTAX_DEFAULT_ARG);
	token = (t_token *)node->content;
	return (token->str);
}

// validate parenthesis
// validate redirect syntax
static bool	is_valid_pre_parse_syntax_inter(t_deque_node *node)
{
	const char		*err_arg;
	t_deque_node	*head_node;

	head_node = node;
	if (!is_parenthesis_concatenated_all(&node))
	{
		err_arg = get_syntax_error_arg(node);
		puterr_msg_quoted_arg(ERROR_MSG_SYNTAX, err_arg);
		return (false);
	}
	node = head_node;
	if (!is_valid_redirect_syntax_all(&node))
	{
		err_arg = get_syntax_error_arg(node);
		puterr_msg_quoted_arg(ERROR_MSG_SYNTAX, err_arg);
		return (false);
	}
	return (true);
}

bool	is_valid_pre_parse_syntax(const t_deque *tokens, \
									t_context *context, \
									t_result *result)
{
	if (!is_valid_pre_parse_syntax_inter(tokens->node))
	{
		set_error_status_and_result(context, result);
		return (false);
	}
	return (true);
}
