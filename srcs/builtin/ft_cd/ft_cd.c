#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

static void	print_err_set_status(const char *arg, \
									const char *path, \
									int tmp_err, \
									uint8_t *status)
{
	const char	*err_arg;

	if (!path)
	{
		if (!arg || ft_streq(arg, KEY_HOME) || ft_streq(arg, CD_ARG_HOME))
			err_arg = KEY_HOME;
		else
			err_arg = KEY_OLDPWD;
		puterr_cmd_arg_msg_wo_colon(CMD_CD, err_arg, ERROR_MSG_NOT_SET);
	}
	else
		puterr_cmd_arg_msg(CMD_CD, path, strerror(tmp_err));
	*status = CD_ERROR_STATUS;
}

static bool	is_valid_cd_path(const char *path, int *tmp_err)
{
	t_result	result;

	if (!path)
		return (false);
	return (is_valid_path(path, tmp_err, &result));
}

static void	print_mv_path_use_oldpwd_or_cdpath(bool is_print_path, \
												const char *pwd)
{
	if (is_print_path)
		ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
}

static void	change_directory(const char *arg, \
								t_context *context, \
								uint8_t *status)
{
	char	*path;
	int		tmp_err;
	char	*absolute_path;
	bool	is_print_path;

	path = cd_set_path(arg, context->var, &is_print_path);
	if (!is_valid_cd_path(path, &tmp_err))
	{
		print_err_set_status(arg, path, tmp_err, status);
		ft_free(&path);
		return ;
	}
	absolute_path = cd_canonicalize_path(path, context->internal_pwd);
	ft_free(&path);
	if (cd_change_dir_to_valid_path(absolute_path, &tmp_err) == FAILURE)
	{
		puterr_cmd_arg_msg(CMD_CD, arg, strerror(tmp_err));
		*status = CD_ERROR_STATUS;
		ft_free(&absolute_path);
		return ;
	}
	cd_update_pwd(absolute_path, context);
	print_mv_path_use_oldpwd_or_cdpath(is_print_path, context->internal_pwd);
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
	change_directory(argv[i], context, &status);
	return (status);
}
