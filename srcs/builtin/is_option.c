#include "ms_builtin.h"

bool	is_option(const char *word)
{
	return (word[0] == CMD_OPTION_MARKER && word[1]);
}
