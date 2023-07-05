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

t_node_kind	convert_kind_token_to_node(t_deque_node *token_node)
{
	t_token			*token;
	t_token_kind	token_kind;

	if (!token_node)
		return (0);//todo: tmp
	token = token_node->content;
	token_kind = token->kind;
	if (token_kind == TOKEN_KIND_OP_AND)
		return (NODE_KIND_OP_AND);
	if (token_kind == TOKEN_KIND_OP_OR)
		return (NODE_KIND_OP_OR);
	if (token_kind == TOKEN_KIND_OP_PIPE)
		return (NODE_KIND_OP_PIPE);
	return (NODE_KIND_NONE); //todo: tmp
}

// <op_list>
// expr	= <com_list> '&&' <com_list>
//		| <com_list> '||' <com_list>
//		| <com_list>
t_ast	*create_operator_list_node(t_deque_node **token_node)
{
	t_ast		*left_node;
	t_ast		*right_node;
	t_node_kind	kind;

	left_node = create_command_list_node(token_node);
	while (*token_node && is_token_kind_and_or(*token_node))
	{
		kind = convert_kind_token_to_node(*token_node); // &&, ||
		*token_node = (*token_node)->next;
		right_node = create_command_list_node(token_node);
		left_node = new_ast_node(kind, left_node, right_node);
	}
	return (left_node);
}

// <com_list>
// term	= <com> '|' <com>
// 		| <com>
t_ast	*create_command_list_node(t_deque_node **token_node)
{
	t_ast		*left_node;
	t_ast		*right_node;
	t_node_kind	kind;

	left_node = create_command_or_subshell_node(token_node);
	while (*token_node && is_token_kind_pipe(*token_node))
	{
		kind = convert_kind_token_to_node(*token_node); // |
		*token_node = (*token_node)->next;
		right_node = create_command_or_subshell_node(token_node);
		left_node = new_ast_node(kind, left_node, right_node);
	}
	return (left_node);
}

// [echo] [a] [b] [|] [cat] [Makefile]

// <com or subshell>
// prim	= <com>
// 		| '(' expr ')'
t_ast	*create_command_or_subshell_node(t_deque_node **token_node)
{
	t_ast		*left_node;
	t_ast		*right_node;
	t_node_kind	kind;

	// command


	// subshell

}
