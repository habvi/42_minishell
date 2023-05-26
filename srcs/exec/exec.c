#include "minishell.h"
#include "deque.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "parser.h"

static t_ast	*get_most_left_leaf(t_ast *root)
{
	t_ast	*node;

	node = root;
	while (node->left)
		node = node->left;
	return (node);
}

static t_ast	*get_next_cmd_node(t_ast *cmd_node)
{
	t_ast	*next_op_node;

	next_op_node = cmd_node->parent;
	if (!next_op_node)
		return (NULL);
	if (next_op_node->left == cmd_node)
		return (next_op_node->right);
	return (get_next_cmd_node(next_op_node)); // pipe only case...??
}

static int	execute_with_pipe(t_ast *cmd, t_fd *fd, int *last_status)
{
	pid_t		pid;
	int			process_result;

	if (x_pipe(fd->pipefd) == PIPE_ERROR)
		return (PIPE_ERROR);
	pid = x_fork();
	if (pid == FORK_ERROR)
		return (PROCESS_ERROR);
	if (pid == CHILD_PID)
		child_process(cmd, fd, false);
	process_result = parent_process(false, fd, pid, last_status);
	return (process_result);
}

static int	execute_without_pipe(t_ast *cmd, t_fd *fd, int *last_status)
{
	pid_t		pid;
	int			process_result;

	pid = x_fork();
	if (pid == FORK_ERROR)
		return (PROCESS_ERROR);
	if (pid == CHILD_PID)
		child_process(cmd, fd, true);
	process_result = parent_process(true, fd, pid, last_status);
	return (process_result);
}

int	execute_command(t_ast *root)
{
	t_fd		fd;
	int			status;
	int			process_result;
	t_ast		*exec_cmd;
	t_ast		*next_cmd;

	init_fd(&fd);
	status = EXIT_SUCCESS;
	exec_cmd = get_most_left_leaf(root);
	while (exec_cmd)
	{
//		print_cmd_node(exec_cmd, "cmd");
		next_cmd = get_next_cmd_node(exec_cmd);
//		print_cmd_node(next_cmd, "next");
		if (next_cmd)
			process_result = execute_with_pipe(exec_cmd, &fd, &status);
		else
			process_result = execute_without_pipe(exec_cmd, &fd, &status);
		if (process_result == PROCESS_ERROR)
			return (PROCESS_ERROR);
		exec_cmd = next_cmd;
	}
	return (status);
}
