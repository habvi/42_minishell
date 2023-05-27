#include <stdlib.h>
#include "ft_builtin.h"
#include "ft_lib.h"
#include "ft_dprintf.h"

//exit [n]
// Exit the shell, returning a status of n to the shell’s parent.
// If n is omitted, the exit status is that of the last command executed.
// Any trap on EXIT is executed before the shell terminates.

// argv[1] == \d or not
// \d is signed int. over long max, it's interpreted as non-numeric argument

// todo: libft ...?
static size_t	cnt_2d_array(const char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

// argv != NULL
static t_exit_arg	validate_argument(const char **cmds)
{
	long	long_num;
	size_t	argc;

	argc = cnt_2d_array(cmds);
	if (argc == 1)
		return (EXIT_VALID_ARG);
	if (!ft_strtol(cmds[1], &long_num, true))
		return (EXIT_NON_NUMERIC_ARG);
	if (argc > 2)
		return (NOT_EXIT_TOO_MANY_NUMERIC_ARG);
	return (EXIT_VALID_ARG);
}

// ft_strtol returns true
static int	get_exit_status(const char *arg, \
							t_exit_arg res, int latest_status)
{
	long	long_num;

	if (res == NOT_EXIT_TOO_MANY_NUMERIC_ARG || res == EXIT_NON_NUMERIC_ARG)
		return (2);
	if (!arg)
		return (latest_status);
	ft_strtol(arg, &long_num, true);
	return (long_num % 256);
}

static void	exec_exit(const char *arg, t_exit_arg res, int status)
{
	if (res == NOT_EXIT_TOO_MANY_NUMERIC_ARG)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: exit: too many arguments\n");
		return ;
	}
	if (res == EXIT_NON_NUMERIC_ARG)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: exit: %s: numeric argument required\n", arg);
		exit (status);
	}
	exit (status);
}

// cmds[0] == "exit"
int	ft_exit(char **cmds)
{
	int			status;
	t_exit_arg	arg_result;

	status = EXIT_SUCCESS; // todo: get latest status
	arg_result = validate_argument((const char **)cmds);
	status = get_exit_status((const char *)cmds[1], arg_result, status);
	exec_exit((const char *)cmds[1], arg_result, status);
	return (status);
}
