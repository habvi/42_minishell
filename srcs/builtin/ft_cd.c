#include <stdlib.h>
#include "ms_builtin.h"
#include "ft_dprintf.h"

uint8_t	ft_cd(const char *const *argv, t_context *context)
{
	(void)argv;
	(void)context;
	ft_dprintf(2, "cd\n");
	return (EXIT_SUCCESS);
}
