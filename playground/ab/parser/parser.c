#include "parser.h"
#include "deque.h"

void	error_exit(const char *func_name, const char *msg)
{
	dprintf(STDERR_FILENO, "Error(%s): %s\n", func_name, msg);
	exit(EXIT_FAILURE);
}
