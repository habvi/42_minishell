#include <stdio.h>
#include <stdlib.h>
#include "ft_builtin.h"
#include "ft_dprintf.h"
#include "minishell.h"
#include "ft_string.h"

// {"exit", "valid_arg", "invalid_arg1", "invalid_arg2", ..., NULL};

static t_exit_arg	validate_argument(const char **cmds)
{
	long	long_num;
	size_t	argc;
	bool	is_legal_num;

	argc = count_2d_array(cmds);
	if (argc == EXIT_ONLY_CMD_CNT)
		return (EXIT_VALID_ARG);
	is_legal_num = ft_legal_number(cmds[EXIT_ARG_IDX], &long_num);
	if (!is_legal_num)
		return (EXIT_NON_NUMERIC_ARG);
	if (argc > VALID_ARG_CNT)
		return (RETURN_TOO_MANY_NUMERIC_ARG);
	return (EXIT_VALID_ARG);
}

// ft_legal_number returns true
static int	get_exit_status(const char *arg, \
							t_exit_arg res, \
							int latest_status)
{
	long	long_num;

	if (res == RETURN_TOO_MANY_NUMERIC_ARG)
		return (TOO_MANY_ARG_STATUS);
	if (res == EXIT_NON_NUMERIC_ARG)
		return (NON_NUMERIC_ARG_STATUS);
	if (!arg)
		return (latest_status);
	ft_legal_number(arg, &long_num);
	return ((int)(long_num & ((1U << BIT_SHIFT_FOR_STATUS) - 1)));
}

static void	put_exit_err(const char *arg, t_exit_arg res)
{
	if (res == RETURN_TOO_MANY_NUMERIC_ARG)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: exit: too many arguments\n");
	}
	else if (res == EXIT_NON_NUMERIC_ARG)
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: exit: %s: numeric argument required\n", arg);
	}
}

static bool	is_exit(t_exit_arg res)
{
	if (res == RETURN_TOO_MANY_NUMERIC_ARG)
		return (false);
	return (true);
}

//const char	*get_res_char(t_exit_arg res)
//{
//	if (res == EXIT_VALID_ARG)
//		return ("EXIT_VALID_ARG");
//	if (res == EXIT_NON_NUMERIC_ARG)
//		return ("EXIT_NON_NUMERIC_ARG");
//	if (res == RETURN_TOO_MANY_NUMERIC_ARG)
//		return ("RETURN_TOO_MANY_NUMERIC_ARG");
//	return ("ERROR");
//}

//exit [n]
// Exit the shell, returning a status of n to the shell’s parent.
// If n is omitted, the exit status is that of the last command executed.
// Any trap on EXIT is executed before the shell terminates.

// argv[1] == \d or not
// \d is signed int. over long max, it's interpreted as non-numeric argument

// cmds[0] == "exit"

int	ft_exit(const char **cmds, bool *is_exit_shell)
{
	int			status;
	t_exit_arg	arg_result;

	arg_result = validate_argument(cmds);
	status = EXIT_SUCCESS; // todo: get latest status
	status = get_exit_status(cmds[EXIT_ARG_IDX], arg_result, status);
	put_exit_err((const char *)cmds[EXIT_ARG_IDX], arg_result);
	if (is_exit_shell)
		*is_exit_shell = is_exit(arg_result);
	return (status);
}
// todo: return to main, exit prompt loop and put 'exit\n' to stderr
