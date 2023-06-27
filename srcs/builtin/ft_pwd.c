#include <errno.h>
#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

// pwd arg1 arg2 arg3 ... -> pwd, $?=0
// pwd op                 -> invalid op, $?=2

static char	*get_pwd(t_params *params)
{
	char	*pwd;
	int		tmp_errno;

	if (params->pwd)
	{
		pwd = ft_strdup(params->pwd);
		return (pwd);
	}
	pwd = get_workind_directory(&tmp_errno, CMD_PWD);
	if (!pwd)
		return (NULL);
	return (pwd);
}

// use getcwd to original error handling.
uint8_t	ft_pwd(const char *const *argv, t_params *params)
{
	uint8_t	status;
	size_t	i;
	char	*pwd;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	pwd = get_pwd(params);
	if (!pwd)
		return (EXIT_FAILURE); // todo:tmp
	ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
	ft_free(&pwd);
	return (status);
}
