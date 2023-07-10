#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

static uint8_t	execute_builtin_command(const char *const *argv, \
										t_context *context)
{
	uint8_t	exec_status;

	exec_status = call_builtin_command(argv, context);
	return (exec_status);
}

static uint8_t	execute_subshell(t_ast *self_node, t_context *context)
{
	t_ast		*root_node;
	t_result	result;

	root_node = self_node->left;
	root_node->parent = NULL; //todo: NULL?
	result = execute_command(root_node, context);
	if (result == PROCESS_ERROR)
		return (EXIT_FAILURE);
	return (context->status);
}

static uint8_t	execute_command_in_child(t_ast *self_node, \
											char **environ, \
											t_context *context)
{
	char	**argv;
	uint8_t	status;

	argv = convert_command_to_argv(self_node->command);
	if (is_command_builtin(argv[0]))
		status = execute_builtin_command((const char *const *)argv, context);
	else if (self_node->kind == NODE_KIND_SUBSHELL)
		status = execute_subshell(self_node, context);
	else
	{
		status = execute_external_command((char *const *)argv, \
											environ, \
											context);
	}
	free_2d_array(&argv);
	return (status);
}

// if execve erorr, no need for auto perror.
void	child_process(t_ast *self_node, \
						char **environ, \
						t_context *context)
{
	uint8_t	status;

	// debug_func(__func__, __LINE__);
	// debug_2d_array(argv);
	if (handle_child_pipes(self_node) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	status = execute_command_in_child(self_node, environ, context);
	exit (status);
}
