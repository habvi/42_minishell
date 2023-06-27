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

bool	is_end_of_option(const char *word)
{
	const size_t	len = ft_strlen(word);

	if (!word)
		return (false);
	if (len != 2)
		return (false);
	return (word[0] == CMD_OPTION_MARKER && word[1] == CMD_OPTION_MARKER);
}
