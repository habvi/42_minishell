#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

// validate parenthesis
// validate redirect syntax
static bool	is_valid_pre_parse_syntax_inter(t_deque_node *node)
{
	if (!is_parenthesis_concatenated_all(node))
	{
		ft_dprintf(2, "error : concat paren\n");
		return (false);
	}
	if (!is_valid_redirect_syntax_all(node))
	{
		ft_dprintf(2, "error : syntax error redirect\n");
		return (false);
	}
	return (true);
}

bool	is_valid_pre_parse_syntax(t_deque *tokens, \
									t_context *context, \
									t_result *result)
{
	t_deque_node	*head_node;

	head_node = tokens->node;
	if (!is_valid_pre_parse_syntax_inter(head_node))
	{
		set_error_status(context, result);
		ast_print_error(head_node);
		return (false);
	}
	return (true);
}
