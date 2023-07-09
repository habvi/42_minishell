#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

// validate parenthesis
// validate redirect syntax
static bool	is_valid_pre_parse_syntax(t_deque_node *node)
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

// todo: tmp destroy func
static void	*destroy_tokens_and_ast(t_deque **tokens, \
									t_ast **ast, \
									bool is_print_error, \
									t_deque_node *head_node)
{
	// debug_print_ast_tree(*ast, __func__);
	if (ast)
		destroy_ast_tree(ast);
	if (is_print_error)
		ast_print_error(head_node);
	destroy_tokens(tokens, del_token);
	return (NULL);
}

// always free tokens
t_ast	*parse(t_deque **tokens, t_context *context)
{
	t_ast			*ast;
	t_deque_node	*head_node;
	t_result		heredoc_result;

	if (deque_is_empty(*tokens))
		return (destroy_tokens_and_ast(tokens, NULL, false, NULL));
	head_node = (*tokens)->node;
	if (!is_valid_pre_parse_syntax(head_node))
	{
		context->status = SYNTAX_ERROR; // todo: print syntax error
		return (destroy_tokens_and_ast(tokens, NULL, false, head_node));
	}
	ast = create_operator_list_node(&head_node, context);
	if (head_node)
		context->status = SYNTAX_ERROR;
	if (context->status == SYNTAX_ERROR)
		return (destroy_tokens_and_ast(tokens, &ast, true, head_node));
	heredoc_result = execute_heredoc(ast);
	if (heredoc_result == PROCESS_ERROR)
		return (destroy_tokens_and_ast(tokens, &ast, false, head_node));
//	debug_print_ast_tree(ast, __func__);
	destroy_tokens(tokens, del_token); //when exec by ast, destroy tokens.
	return (ast);
}
