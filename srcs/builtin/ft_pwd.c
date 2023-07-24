#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"

// pwd arg1 arg2 arg3 ... -> pwd, $?=0
// pwd op                 -> invalid op, $?=2
static char	*get_pwd(t_context *context)
{
	char	*pwd;

	if (context->internal_pwd)
	{
		pwd = x_ft_strdup(context->internal_pwd);
		return (pwd);
	}
	pwd = get_working_directory(CMD_PWD);
	if (!pwd)
		return (NULL);
	return (pwd);
}

// stdout
uint8_t	ft_pwd(const char *const *argv, t_context *context)
{
	uint8_t	status;
	size_t	i;
	char	*pwd;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	pwd = get_pwd(context);
	if (!pwd)
		return (EXIT_FAILURE);
	ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
	ft_free((void **)&pwd);
	return (status);
}
