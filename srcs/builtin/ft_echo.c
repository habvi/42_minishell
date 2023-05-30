#include <stdbool.h>
#include <stdlib.h>
#include "ft_builtin.h"
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
	i = 0;
	while (str[i] == '-')
		i++;
	if (i != 1 || str[i] != 'n')
		return (false);
	while (str[i] == 'n')
		i++;
	if (str[i])
		return (false);
	return (true);
}

static void	skip_option_part(const char **cmds, size_t *idx, bool *is_valid_op)
{
	*is_valid_op = false;
	if (!cmds)
		return ;
	while (cmds[*idx] && is_n_option(cmds[*idx]))
		*idx += 1;
	*is_valid_op = *idx > 1;
}

static void	put_strings(const char **strs)
{
	size_t	idx;

	idx = 0;
	while (strs && strs[idx])
	{
		ft_dprintf(STDOUT_FILENO, "%s", strs[idx]);
		idx++;
		if (strs[idx])
			ft_dprintf(STDOUT_FILENO, " ");
	}
}

// cmds != NULL
// cmds[0] == "echo"
int	ft_echo(const char **cmds)
{
	const int	status = EXIT_SUCCESS;
	size_t		idx;
	bool		is_n_op_validate;

	idx = 1;
	skip_option_part(cmds, &idx, &is_n_op_validate);
	put_strings(&cmds[idx]);
	if (!is_n_op_validate)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (status);
}
