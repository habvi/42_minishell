#include <stdlib.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"

bool	is_absolute_path(const char *path)
{
	if (!path)
		return (false);
	return (path[0] == ABSOLUTE_PATH_HEAD);
}

// if cd_check_current_exist() failure, continue.
// after cd_update_pwd(), not free new_path.
static t_result	change_directory_to_valid_path(const char *arg, \
												const char *path, \
												t_context *context)
{
	char		*new_path;
	t_result	result;
	const char	*internal_pwd = context->internal_pwd;

	result = cd_check_current_exist(internal_pwd);
	if (result == PROCESS_ERROR)
		return (result);
	new_path = cd_create_path_with_pwd(arg, path, internal_pwd, &result);
	if (result == PROCESS_ERROR || result == FAILURE)
	{
		ft_free((void **)&new_path);
		return (result);
	}
	result = cd_check_new_path_exist(arg, &new_path, path, internal_pwd);
	if (result == PROCESS_ERROR || result == FAILURE)
	{
		ft_free((void **)&new_path);
		return (result);
	}
	cd_update_pwd(new_path, context);
	return (SUCCESS);
}

static void	print_mv_path_use_oldpwd_or_cdpath(bool is_print_path, \
												const char *pwd)
{
	if (is_print_path)
		ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
}

static t_result	change_directory(const char *arg, t_context *context)
{
	char		*path;
	bool		is_print_path;
	t_result	result;

	path = cd_set_path(arg, context->var, &is_print_path);
	if (!path)
		return (FAILURE);
	// ft_dprintf(2, "%s: %s, %s\n", __func__, context->internal_pwd, path);
	result = change_directory_to_valid_path(arg, path, context);
	ft_free((void **)&path);
	if (result == PROCESS_ERROR || result == FAILURE)
		return (result);
	print_mv_path_use_oldpwd_or_cdpath(is_print_path, context->internal_pwd);
	return (SUCCESS);
}

uint8_t	ft_cd(const char *const *argv, t_context *context)
{
	uint8_t		status;
	size_t		i;
	size_t		args;
	t_result	result;

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
	result = change_directory(argv[i], context);
	if (result == PROCESS_ERROR || result == FAILURE)
		status = CD_ERROR_STATUS;
	return (status);
}
