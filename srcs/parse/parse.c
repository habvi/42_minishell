#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

// validate parenthesis
// validate redirect syntax
static bool	is_valid_pre_parse_syntax(t_deque_node *node)
{
	// 連続する()の有無チェック
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

// always free tokens
t_ast	*parse(t_deque *tokens, t_context *context)
{
	t_ast			*ast;
	t_deque_node	*head_node;

	if (!is_valid_pre_parse_syntax(tokens->node))
	{
		context->status = SYNTAX_ERROR; // todo: print syntax error
		destroy_tokens(tokens, del_token);
		return (false);
	}
	head_node = tokens->node;
	// todo: status syntax error
	// todo: tokens NULL??
	ast = create_operator_list_node(&head_node);
	// destroy_tokens(tokens, del_token); // todo: parse done, destroy on
	return (ast);
}
