#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"
#include "ft_string.h"

// return true if valid option exist
bool	skip_valid_options(const char *const *argv, \
							size_t *idx, \
							char marker, \
							char op_chr)
{
	if (!argv)
		return (false);
	while (argv[*idx] && is_arg_option(argv[*idx], marker, op_chr))
		*idx += 1;
	if (*idx == 0)
		return (false);
	return (true);
}

bool	is_arg_option(const char *arg, char marker, char op_chr)
{
	size_t	i;

	if (!arg)
		return (false);
	if (!is_option(arg, marker))
		return (false);
	i = 1;
	while (arg[i] == op_chr)
		i++;
	if (arg[i])
		return (false);
	return (true);
}

// option is `-[^-]`
// `--` is not option
bool	is_option(const char *word, char marker)
{
	if (!word)
		return (false);
	if (word[0] != marker)
		return (false);
	if (!word[1] || word[1] == marker)
		return (false);
	return (true);
}

// `--`
bool	is_end_of_option(const char *word)
{
	return (ft_streq(word, END_OF_CMD_OPTION));
}

bool	is_valid_option(const char *const *argv, uint8_t *status, size_t *i)
{
	if (is_option(argv[*i], CMD_OPTION_MARKER))
	{
		*status = INVALID_OPTION;
		// print_error(cmd_name, message); // todo
		ft_dprintf(STDERR_FILENO, "%s: %s: %c%c: %s\n", SHELL_NAME, \
					argv[0], CMD_OPTION_MARKER, argv[*i][1], \
					ERROR_MSG_INVALID_OP);
		return (false);
	}
	if (is_end_of_option(argv[*i]))
		(*i)++;
	return (true);
}
