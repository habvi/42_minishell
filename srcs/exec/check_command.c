#include <unistd.h>
#include "ft_deque.h"

//bool	is_first_command(int prev_fd)
//{
//	return (prev_fd == STDIN_FILENO);
//}

bool	is_last_command(t_deque_node *next_cmd)
{
	return (!next_cmd);
}
