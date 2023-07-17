#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ft_dprintf.h"

// {"exit", "valid_arg", "invalid_arg1", "invalid_arg2", ..., NULL};
static t_exit_arg	validate_argument(const char *const *argv)
{
	long	long_num;
	size_t	argc;
	bool	is_legal_num;

	argc = count_argv(argv);
	if (argc == EXIT_ONLY_CMD_CNT)
		return (EXIT_VALID_ARG);
	is_legal_num = str_to_legal_number(argv[EXIT_ARG_IDX], &long_num);
	if (!is_legal_num)
		return (EXIT_NON_NUMERIC_ARG);
	if (argc > VALID_ARG_CNT)
		return (RETURN_TOO_MANY_NUMERIC_ARG);
	return (EXIT_VALID_ARG);
}

// str_to_legal_number returns true
static uint8_t	get_exit_status(const char *arg, \
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
	str_to_legal_number(arg, &long_num);
	return ((uint8_t)(long_num & BYTE_MASK));
}

static void	put_exit_err(const char *arg, t_exit_arg res)
{
	if (res == RETURN_TOO_MANY_NUMERIC_ARG)
		puterr_cmd_msg(CMD_EXIT, ERROR_MSG_TOO_MANY_ARG);
	else if (res == EXIT_NON_NUMERIC_ARG)
		puterr_cmd_arg_msg(CMD_EXIT, arg, ERROR_MSG_REQUIRED_NUM);
}

static bool	is_exit(t_exit_arg res)
{
	if (res == RETURN_TOO_MANY_NUMERIC_ARG)
		return (false);
	return (true);
}

//exit [n]
// Exit the shell, returning a status of n to the shell’s parent.
// If n is omitted, the exit status is that of the last command executed.
// Any trap on EXIT is executed before the shell terminates.

// argv[1] == \d or not
// \d is signed int. over long max, it's interpreted as non-numeric argument

// if exit called from interactive shell, output `exit` to the console.

// argv[0] == "exit"
uint8_t	ft_exit(const char *const *argv, t_context *context)
{
	uint8_t		status;
	t_exit_arg	arg_result;

	arg_result = validate_argument(argv);
	status = get_exit_status(argv[EXIT_ARG_IDX], arg_result, context->status);
	if (context->is_interactive)
		ft_dprintf(STDERR_FILENO, "%s\n", CMD_EXIT);
	put_exit_err(argv[EXIT_ARG_IDX], arg_result);
	if (!is_exit(arg_result))
	{
		context->is_return = true;
		return (status);
	}
	exit(status);
}
