#include "minishell.h"
#include "ft_string.h"
#include "ft_builtin.h"
#include "deque.h"
#include "ft_dprintf.h"
#include "libft.h"

//echo, cd, pwd, export, unset, env, exit
static bool	is_builtin_func(char **command)
{
	if (!command)
		return (false);
	if (is_equal_strings(command[0], "echo"))
		return (true);
	if (is_equal_strings(command[0], "cd"))
		return (true);
	if (is_equal_strings(command[0], "pwd"))
		return (true);
	if (is_equal_strings(command[0], "export"))
		return (true);
	if (is_equal_strings(command[0], "unset"))
		return (true);
	if (is_equal_strings(command[0], "env"))
		return (true);
	if (is_equal_strings(command[0], "exit"))
		return (true);
	return (false);
}

static int	exec_builtin_func(char **command)
{
	if (!command)
		return (FATAL_ERROR);
	if (is_equal_strings(command[0], "echo"))
		return (ft_echo(command));
//	if (is_equal_strings(command[0], "cd"))
//		return (true);
//	if (is_equal_strings(command[0], "pwd"))
//		return (true);
//	if (is_equal_strings(command[0], "export"))
//		return (true);
//	if (is_equal_strings(command[0], "unset"))
//		return (true);
//	if (is_equal_strings(command[0], "env"))
//		return (true);
	if (is_equal_strings(command[0], "exit"))
		return (ft_exit(command));
	return (FATAL_ERROR);
}

// use PROMPT_NAME
// if execve erorr, no need for auto perror.
void	child_process(t_command *cmd, t_fd *fd, char **environ)
{
	char	**command;
	int		exec_status;

	command = cmd->exec_command;
	// debug_func(__func__, __LINE__);
	// debug_2d_array(command);
	if (handle_child_pipes(cmd, fd) == PROCESS_ERROR)
		exit(EXIT_FAILURE);
	if (is_builtin_func(command))
	{
		exec_status = exec_builtin_func(command);
		deque_clear_all(&cmd->head_command);
		exit(exec_status);
	}
	if (execve(command[0], command, environ) == EXECVE_ERROR)
	{
		// write or malloc error..?
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
											command[0], EXIT_MSG_NO_SUCH_FILE);
		deque_clear_all(&cmd->head_command);
		exit(EXIT_CODE_NO_SUCH_FILE);
	}
}
