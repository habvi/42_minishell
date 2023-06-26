#include "minishell.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_mem.h"
#include "ft_sys.h"

// | command                  -> not handle yet
// command arg                -> return NULL
// command arg |              -> return NULL
// command arg | command2 arg -> return command2
t_deque_node	*get_next_command(t_deque_node *cmd, size_t *cmd_size)
{
	*cmd_size = 0;
	while (cmd && !ft_streq(cmd->content, "|"))
	{
		cmd = cmd->next;
		(*cmd_size)++;
	}
	if (cmd)
	{
		// todo : ft_free -> valgrind error...
		free(cmd->content);
		cmd->content = NULL;
		cmd = cmd->next;
	}
	return (cmd);
}

char	**convert_command_to_array(t_deque_node *cmd, const size_t size)
{
	char	**command;
	char	*tmp;
	size_t	i;

	command = (char **)x_malloc(sizeof(char *) * (size + 1));
	if (!command)
		ft_abort();
	i = 0;
	while (i < size)
	{
		tmp = cmd->content;
		cmd->content = NULL;
		command[i] = tmp;
		cmd = cmd->next;
		i++;
	}
	command[i] = NULL;
	return (command);
}
