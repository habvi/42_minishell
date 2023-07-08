#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

/*
arithmetic
  expression	= term, [(+|-) term]*
  term	    	= primary, [(*|/) primary]*
  primary    	= num | '(' expr ')'

 minishell
<subshell>          ::= '(' <operator_list> ')'

<pipeline_commands> ::= <pipeline_commands> '|' <pipeline_commands>
                      | <command_list>

<operator_list>     ::= <operator_list> '&&' <operator_list>
                      | <operator_list> '||' <operator_list>
                      | <pipeline_commands>
*/

static char *get_token_node_str(t_deque_node *node)
{
	t_token  *token;

	if (!node)
		return (NULL);
	token = (t_token *)node->content;
	return (token->str);
}

#include <stdio.h>
// <op_list>
// expr	= <com_list> '&&' <com_list>
//		| <com_list> '||' <com_list>
//		| <com_list>
t_ast	*create_operator_list_node(t_deque_node **token_node, \
									t_context *context)
{
	t_ast		*left_node;
	t_ast		*right_node;
	t_node_kind	kind;

	left_node = create_command_list_node(token_node, context);
	if (!left_node)
		return (NULL);
	while (*token_node && is_token_kind_and_or_from_node(*token_node))
	{
		if (context->status == SYNTAX_ERROR)
			break ;
		kind = convert_kind_token_to_node(*token_node); // &&, ||
		*token_node = (*token_node)->next;
		right_node = create_command_list_node(token_node, context);
		left_node = new_ast_node(kind, left_node, right_node);
	}
	return (left_node);
}

// <com_list>
// term	= <com> '|' <com>
// 		| <com>
t_ast	*create_command_list_node(t_deque_node **token_node, t_context *context)
{
	t_ast		*left_node;
	t_ast		*right_node;
	t_node_kind	kind;

	left_node = create_command_or_subshell_node(token_node, context);
	if (!left_node)
		return (NULL);
	while (*token_node && is_token_kind_pipe_from_node(*token_node))
	{
		if (context->status == SYNTAX_ERROR)
			break ;
		kind = convert_kind_token_to_node(*token_node); // |
		*token_node = (*token_node)->next;
		right_node = create_command_or_subshell_node(token_node, context);
		left_node = new_ast_node(kind, left_node, right_node);
	}
	return (left_node);
}

static t_ast	*create_command_leaf(t_deque_node **token_node)
{
	t_ast	*ast_node;

	ast_node = new_command_leaf();
	dup_command_from_tokens(ast_node->command, token_node);
	return (ast_node);
}

static t_ast	*create_subshell_node(t_deque_node **token_node, \
										t_context *context)
{
	t_ast	*ast_node;

	if (is_token_kind_paren_left_as_ast_node(*token_node))
	{
		*token_node = (*token_node)->next;
		if (is_token_kind_paren_right_as_ast_node(*token_node))
			return (NULL);
		ast_node = create_operator_list_node(token_node, context);
	}
	if (is_token_kind_paren_right_as_ast_node(*token_node))
	{
		*token_node = (*token_node)->next;
		ast_node = new_subshell_node(ast_node);
		dup_redirection_from_tokens(ast_node->command, token_node);
		return (ast_node);
	}
	return (NULL);
}

// [echo] [a] [b] [|] [cat] [Makefile]

// <com or subshell>
// prim	= <com>
// 		| '(' expr ')'
t_ast	*create_command_or_subshell_node(t_deque_node **token_node, \
											t_context *context)
{
	t_ast	*ast_node;

	if (!*token_node)
	{
		context->status = SYNTAX_ERROR;
		return (NULL);
	}
	ast_node = NULL;
	if (is_token_kind_command_as_ast_node(*token_node))
		ast_node = create_command_leaf(token_node);
	else if (is_token_kind_subshell_as_ast_node(*token_node))
		ast_node = create_subshell_node(token_node, context);
	if (!ast_node)
		context->status = SYNTAX_ERROR;
	return (ast_node);
}
