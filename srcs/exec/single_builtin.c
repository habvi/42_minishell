#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"

char	*get_head_token_str(const t_deque *command)
{
	t_token	*token;

	if (!command)
		return (NULL);
	if (deque_is_empty(command))
		return (NULL);
	token = (t_token *)command->node->content;
	return (token->str);
}

// &&, ||, subshell, command, (ex |)
bool	is_single_builtin_command(const t_ast *self_node)
{
	const t_ast	*parent_node = self_node->parent;
	char		*cmd;

	if (self_node->kind != NODE_KIND_COMMAND)
		return (false);
	cmd = get_head_token_str(self_node->command);
	if (!is_command_builtin(cmd))
		return (false);
	if (parent_node && parent_node->kind == NODE_KIND_OP_PIPE)
		return (false);
	return (true);
}

t_result	execute_single_builtin(t_ast *self_node, t_context *context)
{
	int			stdin_copy;
	int			stdout_copy;
	char		**argv;
	t_result	redirect_result;

	if (backup_stdio_fd(&stdin_copy, &stdout_copy, self_node) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	redirect_result = redirect_fd(self_node, context);
	if (redirect_result == PROCESS_ERROR || redirect_result == FAILURE)
	{
		if (restore_stdio_fd(stdin_copy, stdout_copy) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		return (redirect_result);
	}
	argv = convert_command_to_argv(self_node->command);
	context->status = call_builtin_command((const char *const *)argv, context);
	free_2d_array(&argv);
	if (restore_stdio_fd(stdin_copy, stdout_copy) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}
