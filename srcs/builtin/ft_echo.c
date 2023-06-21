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

static bool	is_n_option(const char *str)
{
	size_t	i;

	if (!str)
		return (false);
	if (str[0] != CMD_OPTION_MARKER || str[1] != ECHO_OPTION)
		return (false);
	i = 1;
	while (str[i] == ECHO_OPTION)
		i++;
	if (str[i])
		return (false);
	return (true);
}

static void	skip_option_part(char *const *argv, size_t *idx, bool *is_valid_op)
{
	*is_valid_op = false;
	if (!argv)
		return ;
	while (argv[*idx] && is_n_option(argv[*idx]))
		*idx += 1;
	*is_valid_op = *idx > 1;
}

static void	put_strings(char *const *strs)
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
int	ft_echo(char *const *argv)
{
	size_t	idx;
	bool	is_n_op_validate;

	idx = 1;
	skip_option_part(argv, &idx, &is_n_op_validate);
	put_strings(&argv[idx]);
	if (!is_n_op_validate)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (EXIT_SUCCESS);
}
