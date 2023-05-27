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

typedef enum e_exit_arg
{
	EXIT_VALID_ARG,
	EXIT_TOO_MANY_NUMERIC_ARG,
	EXIT_NON_NUMERIC_ARG,
}	t_exit_arg;

// argv != NULL
static t_exit_arg	validate_argument(const char **cmds)
{
	long	long_num;
	size_t	argc;

	argc = cnt_2d_array(cmds);
	if (argc == 1)
		return (EXIT_VALID_ARG);
	if (!ft_strtol(cmds[1], &long_num))
		return (EXIT_NON_NUMERIC_ARG);
	if (argc > 2)
		return (EXIT_TOO_MANY_NUMERIC_ARG);
	return (EXIT_VALID_ARG);
}

static int	get_exit_status(const char **cmds, \
							t_exit_arg res, int latest_status)
{
	long	long_num;

	if (res == EXIT_TOO_MANY_NUMERIC_ARG || res == EXIT_NON_NUMERIC_ARG)
		return (2);
	if (!cmds[1])
		return (latest_status);
	ft_strtol(cmds[1], &long_num);
	return (long_num % 256);
}

static void	exec_exit(const char *cmds, t_exit_arg res, int status)
{
	if (res == EXIT_TOO_MANY_NUMERIC_ARG)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: exit: too many arguments\n");
		return ;
	}
	if (res == EXIT_NON_NUMERIC_ARG)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: exit: %s: numeric argument required\n", cmds[1]);
		exit (status);
	}
	exit (status);
}

// cmds[0] == "exit"
int	ft_exit(char **cmds)
{
	int			status;
	t_exit_arg	result;

	status = EXIT_SUCCESS; // todo: get latest status
	result = validate_argument((const char **)cmds);
	status = get_exit_status((const char **)cmds, result, status);
	exec_exit((const char *)cmds, result, status);
	return (status);
}
