#include <stdlib.h>
#include "ft_builtin.h"
//exit [n]
// Exit the shell, returning a status of n to the shell’s parent.
// If n is omitted, the exit status is that of the last command executed.
// Any trap on EXIT is executed before the shell terminates.

// argv[1] == \d or not
// \d is signed int. over long max, it's interpreted as non-numeric argument

int	ft_exit(char **cmds)
{
	int	status;

	(void)cmds;
	status = EXIT_SUCCESS; // todo: get latest status

	return (status);
}
