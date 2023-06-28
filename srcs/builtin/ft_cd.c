#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"

static char	*set_cd_path(const char *arg, t_context *context)
{
	char	*path;

	path = NULL;
	(void)path;
	(void)arg;
	(void)context;
	// if (!arg)
	// 	path = set_home();
	// else
	// 	path = set_arg();
	return (path);
}

static bool	is_valid_cd_path(char *path, uint8_t *status)
{
	(void)path;
	(void)status;
	// free(path)
	return (true);
}

static void	cd_to_valid_path(char *path, t_context *context)
{
	(void)path;
	(void)context;
}

// arg
// NULL   : home
// -      : OLDPWD
// ~      : home
// others : path
static void	change_directory(const char *arg, t_context *context, uint8_t *status)
{
	char	*path;

	path = set_cd_path(arg, context);
	if (!is_valid_cd_path(path, status))
		return ;
	cd_to_valid_path(path, context);
}

uint8_t	ft_cd(const char *const *argv, t_context *context)
{
	uint8_t	status;
	size_t	i;
	size_t	args;

	status = EXIT_SUCCESS;
	i = 1;
	if (!is_valid_option(argv, &status, &i))
		return (status);
	args = count_argv(&argv[i]);
	if (args > 1)
	{
		status = TOO_MANY_ARG_STATUS;
		// print_error();
		return (status);
	}
	change_directory(argv[i], context, &status);
	return (status);
}
