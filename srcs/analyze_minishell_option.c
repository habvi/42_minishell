#include "minishell.h"
#include "ms_builtin.h"

static void	put_option_error(char *arg)
{
	if (arg[0] == CMD_OPTION_MARKER)
		puterr_cmd_msg(arg, ERROR_MSG_INVALID_OP);
	else
		puterr_cmd_msg(arg, ERROR_MSG_INVALID_ARG);
}

static void	skip_while_valid_op(char ***argv, \
									char op_chr, \
									bool *is_forced_interactive)
{
	while (is_arg_option(**argv, CMD_OPTION_MARKER, op_chr))
	{
		(*argv)++;
		*is_forced_interactive = true;
	}
}

t_result	analyze_option(int argc, \
							char **argv, \
							bool *is_forced_interactive, \
							bool *is_test)
{
	*is_forced_interactive = false;
	*is_test = false;
	if (argc == 1)
		return (SUCCESS);
	argv++;
	skip_while_valid_op(&argv, OP_FORCED_INTERACTIVE, is_forced_interactive);
	skip_while_valid_op(&argv, OP_TEST, is_test);
	if (is_end_of_option(*argv))
		argv++;
	if (!*argv)
		return (SUCCESS);
	put_option_error(*argv);
	return (FAILURE);
}
