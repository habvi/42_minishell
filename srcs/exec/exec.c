#include <sys/wait.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"
/*
static void	exec_builtin_in_parent_proc(t_command cmd, \
										t_deque_node *exec_cmd, \
										t_context *context)
{
	size_t	cmd_size;

	cmd.next_command = get_next_command(exec_cmd, &cmd_size);
	cmd.exec_command = convert_command_to_array(exec_cmd, cmd_size);
	context->status = call_builtin_command(\
		(const char *const *)cmd.exec_command, context);
	free_2d_array(&cmd.exec_command);
}

static t_result	dup_process_and_run(t_command *cmd, \
								t_fd *fd, \
								uint8_t *last_status, \
								t_context *context)
{
	extern char	**environ;
	pid_t		pid;

	if (!is_last_command(cmd->next_command))
	{
		if (x_pipe(fd->pipefd) == PIPE_ERROR)
			return (PROCESS_ERROR);
	}
	pid = x_fork();
	if (pid == FORK_ERROR)
		return (PROCESS_ERROR);
	context->is_interactive = false;
	if (pid == CHILD_PID)
		child_process(cmd, fd, environ, context);
	else
	{
		if (parent_process(cmd, fd, pid, last_status) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

t_result	exec_command_iter(t_deque_node *exec_cmd, \
								t_command cmd, \
								t_context *context)
{
	uint8_t	last_status;
	size_t	cmd_size;
	t_fd	fd;

	init_fd(&fd);
	last_status = EXIT_SUCCESS;
	while (exec_cmd)
	{
		cmd.next_command = get_next_command(exec_cmd, &cmd_size);
		cmd.exec_command = convert_command_to_array(exec_cmd, cmd_size);
		if (dup_process_and_run(&cmd, &fd, &last_status, context) \
															== PROCESS_ERROR)
			return (PROCESS_ERROR);
		free_2d_array(&cmd.exec_command);
		exec_cmd = cmd.next_command;
	}
	context->status = last_status;
	return (SUCCESS);
}
 */

///////////////////////////////////////////////////////////////////////////////

static char	*get_head_token_str(t_deque *command)
{
	const t_token	*token = (t_token *)command->node->content;

	return (token->str);
}

char	**convert_command_to_argv(t_deque *command)
{
	char			**argv;
	const size_t	size = command->size;
	size_t			i;
	t_token			*token;
	t_deque_node	*token_node;

	argv = (char **)x_malloc(sizeof(char *) * (size + 1));
	if (!argv)
		ft_abort();
	i = 0;
	token_node = command->node;
	while (token_node)
	{
		token = (t_token *)token_node->content;
		argv[i] = x_ft_strdup(token->str);
		i++;
		token_node = token_node->next;
	}
	argv[i] = NULL;
	return (argv);
}

static void	execute_single_builtin(t_ast *self_node, t_context *context)
{
	char	**argv;

	argv = convert_command_to_argv(self_node->command);
	context->status = call_builtin_command((const char *const *)argv, context);
	free_2d_array(&argv);
}

static bool	is_last_pipe_node(t_ast *self_node, t_ast *parent_node)
{
	if (self_node->kind != NODE_KIND_OP_PIPE)
		return (false);
	if (parent_node && parent_node->kind == NODE_KIND_OP_PIPE)
		return (false);
	return (true);
}

// &&, ||, subshell, command, (ex |)
static bool	is_single_builtin_command(t_ast *self_node, t_ast *parent_node)
{
	char	*cmd;

	if (self_node->kind != NODE_KIND_COMMAND)
		return (false);
	cmd = get_head_token_str(self_node->command);
	if (!is_command_builtin(cmd))
		return (false);
	if (parent_node && parent_node->kind == NODE_KIND_OP_PIPE)
		return (false);
	return (true);
}

// !single builtin commands, &&, ||, |, ()
t_result	exec_command(t_ast *self_node, t_context *context)
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
		if (parent_process(self_node) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	return (SUCCESS);
}

static bool	is_executable_right_node(t_ast *self_node, uint8_t status)
{
	if (!is_node_kind_and_or(self_node->kind))
		return (true);
	if (self_node->kind == NODE_KIND_OP_AND && status == 0)
		return (true);
	if (self_node->kind == NODE_KIND_OP_OR && status != 0)
		return (true);
	return (false);
}

#include <unistd.h>
static void	handle_last_command(t_ast *self_node, t_ast *parent_node, t_context *context)
{
	int	last_status;

	if (self_node->kind != NODE_KIND_OP_PIPE)
		return ;
	if (!is_last_pipe_node(self_node, parent_node))
		return ;
	char c;
	while (read(self_node->prev_fd, &c, 1) > 0)
	{
		write(STDOUT_FILENO, &c, 1);
	}

	waitpid(self_node->pid, &last_status, 0);
	while (wait(NULL) != -1);

	context->status = WEXITSTATUS(last_status);
}

static t_result	execute_command_recursive(t_ast *self_node, \
											t_ast *parent_node, \
											t_context *context)
{
	if (!self_node)
		return (SUCCESS);

	// ( )
	// fork -> execute_command(exec)

	// node
	if (self_node->left)
	{
		if (execute_command_recursive(self_node->left, self_node, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}

	// &&, ||
	if (!is_executable_right_node(self_node, context->status))
		return (CONTINUE);

	// prev_fd = left->pipe_fd[WRITE]
	if (self_node->kind == NODE_KIND_OP_PIPE)
		self_node->right->prev_fd = self_node->left->pipe_fd[READ];

	// node
	if (self_node->right)
	{
		if (execute_command_recursive(self_node->right, self_node, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}

	if (self_node->kind == NODE_KIND_OP_PIPE)
		self_node->prev_fd = self_node->right->prev_fd;

	// |
	// if kind = pipe_node; last pipe node -> fd, wait
	if (self_node->kind == NODE_KIND_OP_PIPE)
	{
		self_node->prev_fd = self_node->right->pipe_fd[READ];
		self_node->pid = self_node->right->pid;
	}

	// command
	if (is_single_builtin_command(self_node, parent_node))
		execute_single_builtin(self_node, context); // todo: process error?
	else if (exec_command(self_node, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	handle_last_command(self_node, parent_node, context);
	return (SUCCESS);
}

t_result	execute_command(t_ast *ast, t_context *context)
{
	t_result	result;

	result = execute_command_recursive(ast, NULL, context);
	return (result);
}
