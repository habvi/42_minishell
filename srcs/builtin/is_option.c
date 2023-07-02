#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"
#include "ft_string.h"

void	skip_option_part(const char *const *argv, \
							size_t *idx, \
							bool *is_valid_op,
							char option)
{
	*is_valid_op = false;
	if (!argv)
		return ;
	while (argv[*idx] && is_arg_option(argv[*idx], option))
		*idx += 1;
	*is_valid_op = *idx > 1;
}

bool	is_arg_option(const char *arg, char option)
{
	size_t	i;

	if (!arg)
		return (false);
	if (!is_option(arg))
		return (false);
	i = 1;
	while (arg[i] == option)
		i++;
	if (arg[i])
		return (false);
	return (true);
}

// option is `-[^-]`
// `--` is not option
bool	is_option(const char *word)
{
	if (!word)
		return (false);
	if (word[0] != CMD_OPTION_MARKER)
		return (false);
	if (!word[1] || word[1] == CMD_OPTION_MARKER)
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
	if (is_option(argv[*i]))
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
