#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"

static char	*get_head_token_str(t_deque *command)
{
	const t_token	*token = (t_token *)command->node->content;

	return (token->str);
}

// &&, ||, subshell, command, (ex |)
bool	is_single_builtin_command(t_ast *self_node)
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

void	execute_single_builtin(t_ast *self_node, t_context *context)
{
	char	**argv;

	argv = convert_command_to_argv(self_node->command);
	context->status = call_builtin_command((const char *const *)argv, context);
	free_2d_array(&argv);
}
