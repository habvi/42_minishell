#include "minishell.h"
#include "ft_lib.h"

char	*x_ft_itoa(int n)
{
	char	*num_str;

	num_str = ft_itoa(n);
	if (!num_str)
		ft_abort();
	return (num_str);
}
