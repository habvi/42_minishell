#include <stdlib.h>
#include "ms_builtin.h"
#include "ms_var.h"

uint8_t	ft_declare(const char *const *argv, t_var *var)
{
	uint8_t	status;
	size_t	idx;
	bool	is_display_attr;

	status = EXIT_SUCCESS;
	idx = 1;
	skip_option_part(argv, &idx, &is_display_attr, DECLARE_OPTION_DISPLAY_ATTR);
	if (!argv[idx])
	{
		var->print_detail(var, VAR_ALL, is_display_attr);
		return (status);
	}
	// change attr
	return (status);
}
