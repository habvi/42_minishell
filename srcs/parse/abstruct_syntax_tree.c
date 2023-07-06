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

static void	print_token_str(t_deque_node *node)
{
	t_token *token;
	char	*str;

	if (!node)
		str = NULL;
	else
	{
		token = (t_token *)node->content;
		str = token->str;
	}
	ft_dprintf(2, "token_str:%s\n", str);
}

t_node_kind	convert_kind_token_to_node(t_deque_node *token_node)
{
	t_token			*token;
	t_token_kind	token_kind;

	if (!token_node)
		return (0);//todo: tmp
	token = token_node->content;
	token_kind = token->kind;
	if (token_kind == TOKEN_KIND_OP_PIPE)
		return (NODE_KIND_OP_PIPE);
	if (token_kind == TOKEN_KIND_OP_OR)
		return (NODE_KIND_OP_OR);
	if (token_kind == TOKEN_KIND_OP_AND)
		return (NODE_KIND_OP_AND);
	if (token_kind == TOKEN_KIND_PAREN_LEFT || token_kind == TOKEN_KIND_PAREN_RIGHT)
		return (NODE_KIND_SUBSHELL);
	if (token_kind == TOKEN_KIND_WORD)
		return (NODE_KIND_COMMAND);
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

static t_token	*dup_token(t_token *token)
{
	t_token	*new_token;

	new_token = init_token_struct();
	new_token->str = x_ft_strdup(token->str);
	new_token->kind = token->kind;
	new_token->quote = token->quote;
	new_token->concat_next = token->concat_next;
	return (new_token);
}

static t_deque_node	*deque_dup_node(t_token *token)
{
	t_deque_node	*new_node;
	t_token			*new_token;

	new_token = dup_token(token);
	new_node = deque_node_new((void *)new_token);
//	ft_dprintf(2, "dup_cmd:%s\n", new_token->str);
	if (!new_node)
		ft_abort();
	return (new_node);
}

static void	dup_command_from_tokens(t_deque *command, t_deque_node **token_node)
{
	t_deque_node	*dup_node;
	t_node_kind		node_kind;

	if (!token_node)
		return ;
	while (*token_node)
	{
		node_kind = convert_kind_token_to_node(*token_node);
		if (node_kind != NODE_KIND_COMMAND && node_kind != NODE_KIND_NONE)
			return ;
		dup_node = deque_dup_node((t_token *)(*token_node)->content);
		deque_add_back(command, dup_node);
		*token_node = (*token_node)->next;
	}
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
		return (NULL);
	token = (t_token *)(*token_node)->content;
	// command
	if (token->kind == TOKEN_KIND_WORD)
	{
//		ft_dprintf(2, "    --------- command ------------------\n");
//		print_token_str(*token_node);
		// debug_token_dq_node(*token_node);
		ast_node = new_command_leaf(NODE_KIND_COMMAND);
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
			ast_node = create_operator_list_node(token_node);
		}
		token = (t_token *)(*token_node)->content;
		if (token->kind == TOKEN_KIND_PAREN_RIGHT)
		{
//			ft_dprintf(2, "      -- ) --\n");
			*token_node = (*token_node)->next;
			return (ast_node);
		}
	}
	token = (t_token *)(*token_node)->content;
	// error
	ft_dprintf(STDERR_FILENO, "%s [%s]\n", \
				"parse: syntax error near unexpected token", token->str);
	return (NULL);
}
