#include "ft_builtin.h"

//exit [n]
// Exit the shell, returning a status of n to the shell’s parent.
// If n is omitted, the exit status is that of the last command executed.
// Any trap on EXIT is executed before the shell terminates.

// <input>								<status>	<exit or not>	<error>
// exit \d$									\d%256		exit
// exit \d+(\s+\d+)*$						1			not			bash: exit: too many arguments
// exit [^0-9\s]$							2			exit		bash: exit: argv[1]: numeric argument required
// exit [^0-9\s]+(\s+[^0-9\s]+)*$			2			exit		bash: exit: argv[1]: numeric argument required
// exit \d+ (\s+[^0-9\s])(\s+[^\s])*$		2			not			bash: exit: too many arguments
// exit [^0-9\s](\s+\d)(\s+[^\s])*$			2		exit		bash: exit: argv[1]: numeric argument required

// \d       : digit
// \s       : space
// [^0-9\s] : printable except 0-9 and space
// [A-Za-z] : alphabet upper and lower
// $        : EOF
// +        : one or more
// *        : zero or more

// argv[1] == \d or not
// \d is signed int. over long max, it's interpreted as non-numeric argument

int	ft_exit(char **cmds)
{
	int	status;

	(void)cmds;
	status = EXIT_SUCCESS; // todo: get latest status


	return (status);
}
