#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

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

//static void	print_token_str(t_deque_node *node)
//{
//	t_token *token;
//	char	*str;
//
//	if (!node)
//		str = NULL;
//	else
//	{
//		token = (t_token *)node->content;
//		str = token->str;
//	}
//	ft_dprintf(2, "token_str:%s\n", str);
//}

// <op_list>
// expr	= <com_list> '&&' <com_list>
//		| <com_list> '||' <com_list>
//		| <com_list>
t_ast	*create_operator_list_node(t_deque_node **token_node)
{
	t_ast		*left_node;
	t_ast		*right_node;
	t_node_kind	kind;

//	ft_dprintf(2, "--------- &&,|| ------------------\n");
//	print_token_str(*token_node);
//	debug_token_dq_node(*token_node);
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

//	ft_dprintf(2, "  --------- | ------------------\n");
//	print_token_str(*token_node);
	// debug_token_dq_node(*token_node);
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
	t_token		*token;
	t_ast		*ast_node;

//	ft_dprintf(2, "    --------- command or subshell------------------\n");
//	print_token_str(*token_node);

	if (!*token_node)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", \
				"parse NULL: syntax error near unexpected token");
		return (NULL);
	}
	token = (t_token *)(*token_node)->content;
	// command
	if (token->kind == TOKEN_KIND_WORD)
	{
//		ft_dprintf(2, "    --------- command ------------------\n");
//		print_token_str(*token_node);
		// debug_token_dq_node(*token_node);
		ast_node = new_command_leaf();
		dup_command_from_tokens(ast_node->command, token_node);
		// debug_print_ast_tree(ast_node, __func__);
		// heredoc
		return (ast_node);
	}
	// subshell
	if (token->kind == TOKEN_KIND_PAREN_LEFT || token->kind == TOKEN_KIND_PAREN_RIGHT)
	{
//		ft_dprintf(2, "    --------- ( )------------------\n");
//		print_token_str(*token_node);
		// debug_token_dq_node(*token_node);
		if (token->kind == TOKEN_KIND_PAREN_LEFT)
		{
//			ft_dprintf(2, "      -- ( --\n");
			*token_node = (*token_node)->next;
			// 
			ast_node = create_operator_list_node(token_node);
		}
		token = (t_token *)(*token_node)->content;
		if (token->kind == TOKEN_KIND_PAREN_RIGHT)
		{
//			ft_dprintf(2, "      -- ) --\n");
			*token_node = (*token_node)->next;
			ast_node = new_subshell_node(ast_node);
			dup_redirection_from_tokens(ast_node->command, token_node);
			return (ast_node);
		}
	}
	token = (t_token *)(*token_node)->content;
	// error
	ft_dprintf(STDERR_FILENO, "%s [%s]\n", \
				"parse: syntax error near unexpected token", token->str);
	return (NULL);
}
