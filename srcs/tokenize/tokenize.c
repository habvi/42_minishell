#include <stdlib.h>
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

static void	add_split_str_to_command(t_deque *command, char *split_str)
{
	char			*str;
	t_deque_node	*node;

	str = ft_strdup(split_str);
	if (!str)
		exit(EXIT_FAILURE);
	node = deque_node_new((void *)str);
	if (!node)
		exit(EXIT_FAILURE);
	deque_add_back(command, node);
}

// line: not NULL
t_deque	*tokenize(char *line)
{
	char	**split_str;
	t_deque	*command;
	size_t	i;

	split_str = ft_split(line, ' ');
	if (!split_str)
		exit(EXIT_FAILURE);
	command = deque_new();
	if (!command)
		exit(EXIT_FAILURE);
	i = 0;
	while (split_str[i])
	{
		add_split_str_to_command(command, split_str[i]);
		i++;
	}
	free_2d_array(&split_str);
	return (command);
}
