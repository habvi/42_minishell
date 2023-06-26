#include <stdbool.h>
#include <stdlib.h>
#include "ms_builtin.h"
#include "ft_dprintf.h"

// valid option
//  {"echo", "-n", NULL}
//  {"echo, "-nnnnnnnn", NULL}
//  {"echo", "-n", "-n", "-nnnn", "-n", "-nnnn", NULL}

// invalid
//  {"echo", "-n" "-nnnnnnm", NULL}
//                 ^^^^^^^^ NOT OPTION
static bool	is_n_option(const char *arg)
{
	size_t	i;

	if (!arg)
		return (false);
	if (!is_option(arg))
		return (false);
	i = 1;
	while (arg[i] == ECHO_OPTION)
		i++;
	if (arg[i])
		return (false);
	return (true);
}

static void	skip_option_part(const char *const *argv, \
								size_t *idx, \
								bool *is_valid_op)
{
	*is_valid_op = false;
	if (!argv)
		return ;
	while (argv[*idx] && is_n_option(argv[*idx]))
		*idx += 1;
	*is_valid_op = *idx > 1;
}

static void	put_strings(const char *const *strs)
{
	size_t	idx;

	idx = 0;
	while (strs && strs[idx])
	{
		ft_dprintf(STDOUT_FILENO, "%s", strs[idx]);
		idx++;
		if (strs[idx])
			ft_dprintf(STDOUT_FILENO, "%c", ECHO_SEPARATOR);
	}
}

// argv != NULL
// argv[0] == "echo"
uint8_t	ft_echo(const char *const *argv)
{
	uint8_t	status;
	size_t	idx;
	bool	is_display_newline;

	status = EXIT_SUCCESS;
	idx = 1;
	skip_option_part(argv, &idx, &is_display_newline);
	put_strings(&argv[idx]);
	if (!is_display_newline)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (status);
}
