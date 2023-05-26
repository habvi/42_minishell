#include <stdbool.h>
#include <stdlib.h>
#include "builtins.h"
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
	if (i != 1)
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
	while (cmds[*i] && is_n_option(cmds[*i]))
		*i += 1;
	*is_valid_op = *i > 1;
}

static void	put_strings(const char **strs)
{
	size_t	i;

	i = 0;
	while (strs && strs[i])
	{
		ft_dprintf(STDIN_FILENO, "%s", strs[i]);
		i++;
		if (strs[i])
			ft_dprintf(STDIN_FILENO, " ",);
	}
}

// cmds != NULL
// cmds[0] == "echo"
int	ft_echo(const char **cmds)
{
	int		status;
	size_t	idx;
	bool	is_n_op_validate;

	status = EXIT_SUCCESS;
	idx = 1;
	skip_option_part(&cmds[1], &idx, &is_n_op_validate);
	put_strings(&cmds[idx]);
	if (!is_n_op_validate)
		ft_dprintf(STDIN_FILENO, "\n");
	return (status);
}
