#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_mem.h"

static uint8_t	execute_builtin_command(const char *const *argv, \
										t_context *context)
{
	uint8_t	exec_status;

	exec_status = call_builtin_command(argv, context);
	return (exec_status);
}

static uint8_t	execute_external_command(char *const *argv, char **environ)
{
	int	exec_status;

	if (argv[0])
		exec_status = execve(argv[0], (char *const *) argv, environ);
	if (!argv[0] || exec_status == EXECVE_ERROR)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", \
					SHELL_NAME, argv[0], ERROR_MSG_CMD_NOT_FOUND); // todo: tmp
	}
	return (EXIT_CODE_NO_SUCH_FILE);
}

// if execve erorr, no need for auto perror.
void	child_process(t_ast *self_node, \
						char **environ, \
						t_context *context)
{
	char	**argv;
	uint8_t	status;

	argv = convert_command_to_argv(self_node->command);
	// debug_func(__func__, __LINE__);
	// debug_2d_array(argv);
	if (handle_child_pipes(self_node) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	if (is_command_builtin(argv[0]))
		status = execute_builtin_command((const char *const *)argv, context);
	else if (self_node->kind == NODE_KIND_SUBSHELL)
	{
		self_node->left->parent = NULL;
		execute_command(self_node->left, context); // todo: process error
		status = context->status;
	}
	else
		status = execute_external_command((char *const *)argv, environ);
	free_2d_array(&argv);
	exit (status);
}
