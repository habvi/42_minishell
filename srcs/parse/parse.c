#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

static t_ast	*create_ast(t_deque_node **head_node, \
							t_deque **tokens, \
							t_context *context, \
							t_result *result)
{
	t_ast	*ast;

	ast = create_operator_list_node(head_node, context);
	if (*head_node)
		set_error_status(context, result);
	if (context->status == SYNTAX_ERROR)
	{
		set_error_status(context, result);
		ast_print_error(*head_node);
		destroy_tokens(tokens, del_token);
		destroy_ast_tree(&ast);
		return (NULL);
	}
	return (ast);
}

// todo: return
// always free tokens
t_ast	*parse(t_deque **tokens, t_context *context, t_result *result)
{
	t_ast			*ast;
	t_deque_node	*head_node;
	t_result		heredoc_result;

	if (deque_is_empty(*tokens))
		return (destroy_tokens(tokens, del_token));
	head_node = (*tokens)->node;
	if (!is_valid_pre_parse_syntax(head_node, tokens, context, result))
		return (NULL);
	ast = create_ast(&head_node, tokens, context, result);
	if (!ast)
		return (NULL);
	heredoc_result = execute_heredoc(ast);
	if (heredoc_result == PROCESS_ERROR)
	{
		destroy_tokens(tokens, del_token);
		destroy_ast_tree(&ast);
		return (NULL);
	}
	destroy_tokens(tokens, del_token);
	return (ast);
}
