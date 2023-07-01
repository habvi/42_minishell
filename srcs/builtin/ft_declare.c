#include <stdlib.h>
#include "ms_builtin.h"
#include "ms_var.h"

uint8_t	ft_declare(const char *const *argv, t_var *var)
{
	uint8_t	status;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	if (!argv[i])
	{
		var->print_detail(var, VAR_ALL);
		return (status);
	}
	return (status);
}
