#include "ms_builtin.h"

//todo: `--`
bool	is_option(const char *word)
{
	if (!word)
		return (false);
	return (word[0] == CMD_OPTION_MARKER && word[1]);
}
