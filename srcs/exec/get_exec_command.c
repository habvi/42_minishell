#include "ft_deque.h"
#include "exec.h"
#include "ft_sys.h"
#include "ft_string.h"

// | command                  -> not handle yet
// command arg                -> return NULL
// command arg |              -> return NULL
// command arg | command2 arg -> return command2
t_deque_node	*get_next_command(t_deque_node *cmd, size_t *cmd_size)
{
	*cmd_size = 0;
	while (cmd && !is_equal_strings(cmd->content, "|"))
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
