#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

static t_ast	*create_ast(t_deque **tokens, \
							t_context *context, \
							t_result *result)
{
	t_deque_node	*head_node;
	t_ast			*ast;

	head_node = (*tokens)->node;
	ast = create_operator_list_node(&head_node, context);
	if (head_node)
		set_error_status(context, result);
	if (context->status == SYNTAX_ERROR)
	{
		set_error_status(context, result);
		ast_print_error(head_node);
		destroy_tokens(tokens, del_token);
		destroy_ast_tree(&ast, *result);
		return (NULL);
	}
	return (ast);
}

// todo: return
// always free tokens
t_ast	*parse(t_deque **tokens, t_context *context, t_result *result)
{
	t_ast		*ast;
	t_result	heredoc_result;

	if (deque_is_empty(*tokens))
		return (destroy_tokens(tokens, del_token));
	if (!is_valid_pre_parse_syntax(tokens, context, result))
		return (NULL);
	ast = create_ast(tokens, context, result);
	if (!ast)
		return (NULL);
	heredoc_result = execute_heredoc(ast);
	if (heredoc_result == PROCESS_ERROR)
	{
		destroy_tokens(tokens, del_token);
		destroy_ast_tree(&ast, *result);
		return (NULL);
	}
	destroy_tokens(tokens, del_token);
	return (ast);
}
