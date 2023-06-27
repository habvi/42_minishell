#include "ms_builtin.h"
#include "ft_string.h"

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
