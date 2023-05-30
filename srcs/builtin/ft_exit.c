#include <stdio.h>
#include <stdlib.h>
#include "ft_builtin.h"
#include "ft_dprintf.h"
#include "minishell.h"

// {"exit", "valid_arg", "invalid_arg1", "invalid_arg2", ..., NULL};
// todo: naming...
#define EXIT_ONLY_CMD_CNT		1
#define EXIT_ARG_IDX			1
#define VALID_ARG_CNT			2

#define NON_NUMERIC_ARG_STATUS	2
#define TOO_MANY_ARG_STATUS		1

// todo: libft ...?
static size_t	cnt_2d_array(const char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

// ft_legal_number returns true
static int	get_exit_status(const char **cmds, \
							t_exit_arg *res, int latest_status)
{
	const size_t	argc = cnt_2d_array(cmds);
	long			long_num;
	bool			is_legal_num;

	if (argc == EXIT_ONLY_CMD_CNT)
	{
		*res = EXIT_VALID_ARG;
		return (latest_status);
	}
	is_legal_num = ft_legal_number(cmds[EXIT_ARG_IDX], &long_num);
	if (!is_legal_num)
	{
		*res = EXIT_NON_NUMERIC_ARG;
		return (NON_NUMERIC_ARG_STATUS);
	}
	if (argc > VALID_ARG_CNT)
	{
		*res = RETURN_TOO_MANY_NUMERIC_ARG;
		return (TOO_MANY_ARG_STATUS);
	}
	*res = EXIT_VALID_ARG;
	return ((int)(long_num & 255));
}

static void	put_err(const char *arg, t_exit_arg res)
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

	status = EXIT_SUCCESS; // todo: get latest status
	status = get_exit_status((const char **)cmds, &arg_result, status);
//	printf("status:%d, res:%s\n", status, get_res_char(arg_result));
	put_err((const char *)cmds[EXIT_ARG_IDX], arg_result);
	if (is_exit_shell)
		*is_exit_shell = is_exit(arg_result);
	return (status);
}
// todo: return to main, exit prompt loop and put 'exit\n' to stderr
