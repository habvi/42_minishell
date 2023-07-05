#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

void	destroy_tmp(t_deque *command, void (*del_token)(void *), t_ast *ast)
{
	if (command)
		destroy_tokens(command, del_token);
	if (ast)
		destroy_ast_tree(&ast);
}

// todo: after parser done, erase this func.
// deque_node->content : only (char *)t_token->str
static t_deque	*tmp_func_convert_to_executable_command(t_deque *tmp_cmds)
{
	t_deque			*cmd;
	t_deque_node	*tmp_node;
	t_token			*token;
	char			*dup_str;
	t_deque_node	*new_node;

	cmd = deque_new();
	if (!cmd)
		ft_abort();
	tmp_node = tmp_cmds->node;
	while (tmp_node)
	{
		token = (t_token *)tmp_node->content;
		dup_str = x_ft_strdup(token->str);
		new_node = deque_node_new((void *)dup_str);
		deque_add_back(cmd, new_node);
		tmp_node = tmp_node->next;
	}
	return (cmd);
}

static t_deque	*tmp_convert(t_deque *tokens, t_ast *ast)
{
	t_deque		*command;

	if (!tokens)
		return (NULL);
	command = tmp_func_convert_to_executable_command(tokens);
	destroy_tmp(tokens, del_token, ast);
	return (command);
}

t_result	read_eval_print_loop(t_context *context)
{
	t_deque		*command;
	t_result	result;
	char		*line;
	t_deque		*tokens;
	t_ast		*ast;

	result = SUCCESS;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		tokens = tokenize(line, context);
		if (context->status != EXIT_SUCCESS)
			continue ;
		ast = parse(tokens, context);
		if (context->status != EXIT_SUCCESS)
			continue ;
		tokens = NULL; // todo: for parse test. erase.
		command = tmp_convert(tokens, ast);
		result = execute_command(command, context);
		destroy_tmp(command, free, ast);
		if (result == PROCESS_ERROR)
			break ;
	}
	return (result);
}
