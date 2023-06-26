#include <errno.h>
#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

// pwd arg1 arg2 arg3 ... -> pwd, $?=0
// pwd op                 -> invalid op, $?=2

// ENOENT return params->pwd
// else error
static bool	is_pwd_error(char *pwd, int tmp_errno)
{
	if (!pwd && tmp_errno != ENOENT)
		return (true);
	return (false);
}

static char	*get_pwd(t_params *params)
{
	char	*pwd;
	int		tmp_errno;

	errno = 0;
	pwd = getcwd(NULL, 0); //todo realloc
	tmp_errno = errno;
	if (tmp_errno == ENOMEM)
		ft_abort();
	if (is_pwd_error(pwd, tmp_errno))
		return (NULL);
	else if (tmp_errno == ENOENT && !params->pwd) //todo
	{
		ft_dprintf(STDERR_FILENO, \
			"pwd: error retrieving current directory: " \
			"getcwd: cannot access parent directories: " \
			"No such file or directory\n");
	}
	else if (tmp_errno == ENOENT)
		pwd = ft_strdup(params->pwd);
	return (pwd);
}

// use getcwd to original error handling.
uint8_t	ft_pwd(const char *const *argv, t_params *params)
{
	uint8_t	status;
	char	*pwd;

	status = EXIT_SUCCESS;
	if (is_option(argv[1]))
	{
		status = INVALID_OPTION; // print error
		return (status);
	}
	pwd = get_pwd(params);
	if (!pwd)
		return (EXIT_FAILURE); // todo:tmp
	ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
	ft_free(&pwd);
	return (status);
}
