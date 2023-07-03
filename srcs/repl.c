#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
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

static void	destroy_command(t_deque *command)
{
	deque_clear_all(&command, free);
}

t_result	read_eval_print_loop(t_context *context)
{
	t_deque		*command;
	t_result	result;
	char		*line;
	t_deque		*tmp_command;

	command = NULL;
	result = SUCCESS;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		tmp_command = tokenize(line, context);
		ft_free(&line);
		if (context->status != EXIT_SUCCESS) // todo: or if !tmp_command
		{
			destroy_command(tmp_command);
			return (FAILURE);
		}
		// >>>>>> todo(erase): for test, temporaly pass only str deque.
		// debug_token_dq(tmp_command, "repl");
		command = tmp_func_convert_to_executable_command(tmp_command);
		deque_clear_all(&tmp_command, del_token);
		// <<<<<<
		result = execute_command(command, context);
		destroy_command(command);
		if (result == PROCESS_ERROR)
			break ;
	}
	return (result);
}
