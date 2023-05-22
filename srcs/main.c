#include "minishell.h"
#include "libft.h"

static void	init_commands(t_command *cmd)
{
	cmd->head = NULL;
	cmd->exec_command = NULL;
}

static int	minishell(void)
{
	char		*line;
	t_command	cmd;
	int			process_status;

	init_commands(&cmd);
	process_status = EXIT_SUCCESS;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		// tokenize
		cmd.head = ft_split(line, ' ');
		free(line);
		if (!cmd.head)
			return (EXIT_FAILURE);
		cmd.exec_command = cmd.head;
		// parse
		process_status = execute_command(&cmd);
		free_2d_array(&cmd.head);
		if (process_status == PROCESS_ERROR)
			return (EXIT_FAILURE);
	}
	return (process_status);
}

int	main(void)
{
	int	process_status;

	process_status = minishell();
	return (process_status);
}
