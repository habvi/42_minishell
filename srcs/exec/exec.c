#include "minishell.h"
#include "deque.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "ft_builtin.h"

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
t_deque_node	*get_next_command(t_deque_node *cmd, size_t *cmd_size)
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

char	**convert_command_to_array(t_deque_node *node, const size_t size)
{
	char	**command;
	char	*tmp;
	size_t	i;

	command = (char **)x_malloc(sizeof(char *) * (size + 1));
	if (!command)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		tmp = node->content;
		node->content = NULL;
		command[i] = tmp;
		node = node->next;
		i++;
	}
	command[i] = NULL;
	return (command);
}

static int	dup_process_and_run(t_command *cmd, t_fd *fd, int *last_exit_status)
{
	extern char	**environ;
	pid_t		pid;

	if (!is_last_command(cmd->next_command))
	{
		if (x_pipe(fd->pipefd) == PIPE_ERROR)
			return (PIPE_ERROR);
	}
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

int	execute_command(t_deque *dq_cmd, bool *is_exit_shell)
{
	t_command		cmd;
	t_fd			fd;
	int				last_exit_status;
	t_deque_node	*node;
	size_t			cmd_size;

	init_cmd(&cmd, dq_cmd);
	init_fd(&fd);
	last_exit_status = EXIT_SUCCESS;
	node = dq_cmd->node;
	if (pipe_cnt(node) == 0 && is_builtin_func((char *)dq_cmd->node->content))
		return (exec_builtin_in_parent_proc(cmd, node, is_exit_shell));
	while (node)
	{
		cmd.next_command = get_next_command(node, &cmd_size);
		cmd.exec_command = convert_command_to_array(node, cmd_size);
		if (dup_process_and_run(&cmd, &fd, &last_exit_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		free_2d_array(&cmd.exec_command);
		node = cmd.next_command;
	}
	return (last_exit_status);
}
