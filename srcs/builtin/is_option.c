#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

// return true if valid option exist
bool	skip_valid_options(const char *const *argv, \
							size_t *i, \
							char marker, \
							char op_chr)
{
	if (!argv)
		return (false);
	while (argv[*i] && is_arg_option(argv[*i], marker, op_chr))
		*i += 1;
	return (*i > 1);
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
// `--x` is not option
bool	is_option(const char *word, char marker)
{
	if (!word)
		return (false);
	if (word[0] != marker)
		return (false);
	if (!word[1])
		return (false);
	if (ft_strncmp(word, END_OF_CMD_OPTION, 2) == 0)
	{
		if (!word[2])
			return (false);
	}
	return (true);
}

// `--`
bool	is_end_of_option(const char *word)
{
	return (ft_streq(word, END_OF_CMD_OPTION));
}

// in minishell, the presence of an option causes an invalid option error
bool	is_valid_option(const char *const *argv, uint8_t *status, size_t *i)
{
	if (is_option(argv[*i], CMD_OPTION_MARKER))
	{
		*status = INVALID_OPTION;
		puterr_arg_op_msg(argv[0], argv[*i][1]);
		return (false);
	}
	if (is_end_of_option(argv[*i]))
		(*i)++;
	return (true);
}
