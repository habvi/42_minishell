#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

// todo: tmp func
static void	print_err_set_status(const char *arg, \
									const char *path, \
									int tmp_err, \
									uint8_t *status)
{
	const char	*err_arg;
	const char	*err_msg;

	if (!path)
	{
		if (!arg || ft_streq(arg, KEY_HOME) || ft_streq(arg, CD_ARG_HOME))
			err_arg = KEY_HOME;
		else
			err_arg = KEY_OLDPWD;
		err_msg = ERROR_MSG_NOT_SET;
		ft_dprintf(STDERR_FILENO, "%s: %s: %s %s\n", \
				SHELL_NAME, CMD_CD, err_arg, err_msg);
	}
	else
	{
		err_arg = path;
		err_msg = strerror(tmp_err);
		ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n", \
				SHELL_NAME, CMD_CD, err_arg, err_msg);
		*status = CD_ERROR_STATUS;
	}
}

static bool	is_valid_cd_path(const char *path, int *tmp_err)
{
	if (!path)
		return (false);
	return (is_valid_path(path, tmp_err));
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
	char		*path;
	int			tmp_err;
	char		*absolute_path;
	t_result	result;
	bool		is_print_path;

	path = cd_set_path(arg, context->var, &is_print_path);
	if (!is_valid_cd_path(path, &tmp_err))
	{
		print_err_set_status(arg, path, tmp_err, status);
		ft_free(&path);
		return ;
	}
	absolute_path = cd_canonicalize_path(path, context->internal_pwd);
	ft_free(&path);
	result = cd_change_dir_to_valid_path(absolute_path, status);
	if (result == FAILURE)
	{
		ft_dprintf(2, "cd: fail to chdir\n"); // todo: tmp
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
		// print_error(); // todo
		return (status);
	}
	change_directory(argv[i], context, &status);
	return (EXIT_SUCCESS);
}
