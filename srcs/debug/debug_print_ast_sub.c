#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_mem.h"

char	*get_tree_symbol(bool is_rhs)
{
	if (is_rhs)
		return ("└");
	return ("├");
}

char	get_tree_space(bool is_rhs)
{
	if (is_rhs)
		return (' ');
	return ('|');
}
