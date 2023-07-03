#include <stdlib.h>
#include "ms_builtin.h"
#include "ms_var.h"

// export declare VAR_ENV
uint8_t	ft_export(const char *const *argv, t_var *var)
{
	uint8_t	status;
	size_t	i;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	if (!argv[i])
	{
		var->print_detail(var, VAR_ENV, true);
		return (status);
	}
	declare_all(&argv[i], var, &status, VAR_ENV);
	return (status);
}
