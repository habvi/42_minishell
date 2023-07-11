#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

static t_ast	*create_ast(t_deque *tokens, \
							t_context *context, \
							t_result *result)
{
	t_deque_node	*head_node;
	t_ast			*ast;
	uint8_t			ast_status;

	ast_status = AST_STATUS_SUCCESS;
	head_node = tokens->node;
	ast = create_operator_list_node(&head_node, &ast_status);
	if (head_node || ast_status == SYNTAX_ERROR)
	{
		set_error_status(context, result);
		ast_print_error(head_node);
		return (NULL);
	}
	return (ast);
}

static void	*destroy_tokens_and_ast(t_deque **tokens, \
									t_ast **ast, \
									t_result result)
{
	destroy_tokens(tokens, del_token);
	destroy_ast_tree(ast, result);
	return (NULL);
}

// todo: return
// always free tokens
t_ast	*parse(t_deque **tokens, t_context *context, t_result *result)
{
	t_ast		*ast;
	t_result	heredoc_result;

	if (deque_is_empty(*tokens))
		return (destroy_tokens(tokens, del_token));
	if (!is_valid_pre_parse_syntax(*tokens, context, result))
		return (destroy_tokens(tokens, del_token));
	ast = create_ast(*tokens, context, result);
	if (!ast)
		return (destroy_tokens_and_ast(tokens, &ast, *result));
	heredoc_result = execute_heredoc(ast);
	if (heredoc_result == PROCESS_ERROR)
		return (destroy_tokens_and_ast(tokens, &ast, *result));
	destroy_tokens(tokens, del_token);
	return (ast);
}
