#include "minishell.h"
#include "deque.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "parser.h"

// use PROMPT_NAME
// if execve erorr, no need for auto perror.
//void	child_process(t_command *cmd, t_fd *fd, char **environ)
//{
//	char	**command;
//
//	command = cmd->exec_command;
//	// debug_func(__func__, __LINE__);
//	// debug_2d_array(command);
//	// if (!command[0])
//	// 	exit(EXIT_SUCCESS);
//	if (handle_child_pipes(cmd, fd) == PROCESS_ERROR)
//		exit(EXIT_FAILURE);
//	if (execve(command[0], command, environ) == EXECVE_ERROR)
//	{
//		// write or malloc error..?
//		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
//		command[0], EXIT_MSG_NO_SUCH_FILE);
//		deque_clear_all(&cmd->head_command);
//		exit(EXIT_CODE_NO_SUCH_FILE);
//	}
//}

static char	**convert_command_to_array(t_deque_node *node, const size_t size)
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

void	child_process(t_ast *cmd, t_fd *fd, bool is_last_command)
{
	char		**command;
	extern char	**environ;

	command = convert_command_to_array(cmd->cmd_head->node, \
										cmd->cmd_head->size);
	// debug_func(__func__, __LINE__);
	// debug_2d_array(command);
	// if (!command[0])
	// 	exit(EXIT_SUCCESS);
	if (handle_child_pipes(is_last_command, fd) == PROCESS_ERROR)
	{
		deque_clear_all(&cmd->cmd_head);
		free_2d_array(&command);
		exit(EXIT_FAILURE);
	}
	if (execve(command[0], command, environ) == EXECVE_ERROR)
	{
		// write or malloc error..?
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", \
											command[0], EXIT_MSG_NO_SUCH_FILE);
		deque_clear_all(&cmd->cmd_head);
		free_2d_array(&command);
		exit(EXIT_CODE_NO_SUCH_FILE);
	}
}
