#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_sys.h"

static bool	is_last_pipe_node(t_ast *self_node)
{
	t_ast	*parent_node;

	if (self_node->kind != NODE_KIND_OP_PIPE)
		return (false);
	parent_node = self_node->parent;
	if (!parent_node)
		return (true);
	if (parent_node->kind != NODE_KIND_OP_PIPE)
		return (true);
	return (false);
}

bool	is_last_command_node(t_ast *self_node)
{
	t_ast	*parent_node;

	// ft_dprintf(2, "============ %s : %d =================\n", get_head_token_str(self_node->command), self_node->kind);
	parent_node = self_node->parent;
	// if (self_node->kind == NODE_KIND_SUBSHELL)
	// 	return (true);
	// if (self_node->kind != NODE_KIND_COMMAND)
	// 	return (false);
	if (!parent_node)
		return (true);
	if (is_last_pipe_node(parent_node) && parent_node->right == self_node)
	{
		ft_dprintf(2, "cat?????\n");
		return (true);
	}
	if (is_node_kind_and_or(parent_node->kind))
		return (true);
	if (parent_node->kind == NODE_KIND_SUBSHELL)
		return (is_last_command_node(parent_node));
	return (false);
}

// !single builtin commands, &&, ||, |, ()
t_result	exec_command_each(t_ast *self_node, t_context *context)
{
	extern char	**environ;

	if (self_node->kind != NODE_KIND_COMMAND)
		return (SUCCESS);

	if (x_pipe(self_node->pipe_fd) == PIPE_ERROR)
		return (PROCESS_ERROR);
	self_node->pid = x_fork();
	if (self_node->pid == FORK_ERROR)
		return (PROCESS_ERROR);
	context->is_interactive = false;
	if (self_node->pid == CHILD_PID)
		child_process(self_node, environ, context);
	else
	{
		if (parent_process(self_node, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
