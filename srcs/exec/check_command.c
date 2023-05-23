#include "minishell.h"

bool	is_first_command(int prev_fd)
{
	return (prev_fd == STDIN_FILENO);
}

bool	is_last_command(char *next_cmd)
{
	return (!next_cmd);
}
