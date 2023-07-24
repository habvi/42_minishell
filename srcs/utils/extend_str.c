#include "minishell.h"
#include "ft_mem.h"

// free left & right, return alloc left.
char	*extend_str(char *left, char *right)
{
	char	*tmp;

	tmp = left;
	left = x_ft_strjoin(tmp, right);
	ft_free((void **)&tmp);
	ft_free((void **)&right);
	return (left);
}
