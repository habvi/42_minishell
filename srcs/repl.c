#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

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

t_result	read_eval_print_loop(t_context *context)
{
	t_deque		*command;
	t_result	result;
	char		*line;
	t_deque		*tokens;
	t_ast		*ast;

	command = NULL;
	result = SUCCESS;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		tokens = tokenize(line, context);
		ft_free(&line);
		if (context->status != EXIT_SUCCESS)
			continue ;
		command = tmp_func_convert_to_executable_command(tokens);
		destroy_tokens(tokens, del_token);
		ast = parse(tokens);
		(void)ast;
		result = execute_command(command, context);
		destroy_tokens(command, free);
		if (result == PROCESS_ERROR)
			break ;
	}
	return (result);
}
