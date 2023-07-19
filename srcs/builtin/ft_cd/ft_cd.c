#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

static void	print_mv_path_use_oldpwd_or_cdpath(bool is_print_path, \
												const char *pwd)
{
	if (is_print_path)
		ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
}

bool	is_absolute_path(const char *path)
{
	return (path[0] == ABSOLUTE_PATH_HEAD);
}

// allocate absolute_path
static t_result	change_directory_to_valid_path(char **absolute_path, \
												const char *arg, \
												const char *path, \
												const char *internal_pwd)
{
	t_result	result;

	*absolute_path = NULL;
	if (is_absolute_path(path))
		result = cd_chdir_from_absolute_path(absolute_path, path);
	else
		result = cd_chdir_from_relative_path(\
									absolute_path, arg, path, internal_pwd);
	if (result == FAILURE)
		ft_free(absolute_path);
	return (result);
}

// in normal case: not free absolute_path
static t_result	change_directory(const char *arg, t_context *context)
{
	char		*path;
	bool		is_print_path;
	t_result	result;
	char		*absolute_path;

	path = cd_set_path(arg, context->var, &is_print_path);
	if (!path)
		return (FAILURE);
	result = change_directory_to_valid_path(\
							&absolute_path, arg, path, context->internal_pwd);
	ft_free(&path);
	if (result == FAILURE)
		return (FAILURE);
	cd_update_pwd(absolute_path, context);
	print_mv_path_use_oldpwd_or_cdpath(is_print_path, context->internal_pwd);
	return (SUCCESS);
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
		puterr_cmd_msg(CMD_CD, ERROR_MSG_TOO_MANY_ARG);
		return (status);
	}
	if (change_directory(argv[i], context) == FAILURE)
		status = CD_ERROR_STATUS;
	return (status);
}
