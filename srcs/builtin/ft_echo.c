#include <stdbool.h>
#include <stdlib.h>
#include "ms_builtin.h"
#include "ft_dprintf.h"

// stdout
static void	put_strings(const char *const *strs)
{
	size_t	i;

	i = 0;
	while (strs && strs[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s", strs[i]);
		i++;
		if (strs[i])
			ft_dprintf(STDOUT_FILENO, "%c", ECHO_SEPARATOR);
	}
}

// valid option
//  {"echo", "-n", NULL}
//  {"echo, "-nnnnnnnn", NULL}
//  {"echo", "-n", "-n", "-nnnn", "-n", "-nnnn", NULL}

// invalid
//  {"echo", "-n" "-nnnnnnm", NULL}
//                 ^^^^^^^^ NOT OPTION

// argv != NULL
// argv[0] == "echo"
uint8_t	ft_echo(const char *const *argv)
{
	uint8_t	status;
	size_t	i;
	bool	is_display_newline;

	status = EXIT_SUCCESS;
	i = 1;
	is_display_newline = skip_valid_options(argv, \
											&i, \
											CMD_OPTION_MARKER, \
											ECHO_OPTION_DISPLAY_NEWLINE);
	put_strings(&argv[i]);
	if (!is_display_newline)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (status);
}
