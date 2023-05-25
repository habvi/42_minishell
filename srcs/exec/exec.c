#include "minishell.h"
#include "deque.h"
#include "ft_dprintf.h"
#include "libft.h"

static bool	is_pipe(const char *str)
{
	if (ft_strnlen(str, 2) == 1 && *str == '|')
		return (true);
	return (false);
}

// | command                  -> not handle yet
// command arg                -> return NULL
// command arg |              -> return NULL
// command arg | command2 arg -> return command2
static t_deque_node	*get_next_command(t_deque_node *cmd, size_t *cmd_size)
{
	*cmd_size = 0;
	while (cmd && !is_pipe(cmd->content))
	{
		cmd = cmd->next;
		(*cmd_size)++;
	}
	if (cmd)
	{
		free(cmd->content);
		cmd->content = NULL;
		cmd = cmd->next;
	}
	return (cmd);
}

static int	dup_process_and_run(t_command *cmd, t_fd *fd, int *last_exit_status)
{
	extern char	**environ;
	pid_t		pid;

	if (!cmd)
		return (0);
	// if (!is_last_command(*cmd->next_command))
	// {
	// 	if (x_pipe(fd->pipefd) == PIPE_ERROR)
	// 		return (PIPE_ERROR);
	// }
	pid = x_fork();
	if (pid == FORK_ERROR)
		return (FORK_ERROR);
	if (pid == CHILD_PID)
		child_process(cmd, fd, environ);
	else
	{
		if (parent_process(cmd, fd, pid, last_exit_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (EXIT_SUCCESS);
}

int	execute_command(t_deque *dq_cmd)
{
	t_fd			fd;
	int				last_exit_status;
	t_command		cmd;
	t_deque_node	*node;
	size_t			cmd_size;

	fd.prev_fd = STDIN_FILENO;
	last_exit_status = EXIT_SUCCESS;
	cmd.head_command = dq_cmd;
	node = dq_cmd->node;
	while (node)
	{
		cmd.next_command = get_next_command(node, &cmd_size);
		printf("[cmd_size: %zu]\n", cmd_size);
		// cmd.exec_command = convert_command_to_array(node, cmd_size);
		if (dup_process_and_run(NULL, NULL, &last_exit_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		// if (dup_process_and_run(cmd, &fd, &last_exit_status) == PROCESS_ERROR)
		// 	return (PROCESS_ERROR);
		node = cmd.next_command;
	}
	return (last_exit_status);
}
