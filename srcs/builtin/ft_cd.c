#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

static bool	is_valid_cd_path(char *path, int *tmp_err)
{
	if (!path)
		return (false);
	if (!test_opendir(path, tmp_err))
		return (false);
	return (true);
}

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
		err_arg = arg;
		err_msg = strerror(tmp_err);
		ft_dprintf(STDERR_FILENO, "%s: %s: %s: %s\n", \
				SHELL_NAME, CMD_CD, err_arg, err_msg);
		*status = CD_ERROR_STATUS;
	}
}

// internalを変える -> 自動的に env->update する方が良さそう
static void	cd_update_pwd(char *path, t_context *context)
{
	t_env	*env;
	char	*pwd_value;
	char	*old_pwd_value;

	env = context->env;
	// ft_dprintf(2, "1 - pwd(i):%s, old(i):%s, PWD(h):%s, OLD(h):%s\n\n", 
	// context->internal_pwd, context->internal_old_pwd, 
	// env->get_value(env, KEY_PWD), env->get_value(env, KEY_OLDPWD));

	ft_free(&context->internal_old_pwd);
	if (env_is_key_exist(env, KEY_PWD)) // to do: env->is_
		context->internal_old_pwd = context->internal_pwd;
	else
		context->internal_old_pwd = NULL;
	context->internal_pwd = path;
	// ft_dprintf(2, "inter_pwd    : %s\n", context->internal_pwd);
	// ft_dprintf(2, "inter_old_pwd: %s\n", context->internal_old_pwd);

	pwd_value = context->internal_pwd;
	old_pwd_value = context->internal_old_pwd;
	if (env->is_key_exist(env, KEY_PWD))
		env_set_dup_key_value_allow_null(env, KEY_PWD, pwd_value, ENV_ADD);
	if (env->is_key_exist(env, KEY_OLDPWD))
		env_set_dup_key_value_allow_null(env, KEY_OLDPWD, old_pwd_value, ENV_ADD);

	// ft_dprintf(2, "2 - pwd(i):%s, old(i):%s, PWD(h):%s, OLD(h):%s\n\n", 
	// context->internal_pwd, context->internal_old_pwd, 
	// env->get_value(env, KEY_PWD), env->get_value(env, KEY_OLDPWD));
}

// arg
// NULL   : home
// -      : OLDPWD
// ~      : home
// others : path
static void	change_directory(const char *arg, \
								t_context *context, \
								uint8_t *status)
{
	char		*path;
	int			tmp_err;
	t_result	result;
	char		*absolute_path;

	path = cd_set_path(arg, context->env);
	if (!is_valid_cd_path(path, &tmp_err))
	{
		print_err_set_status(arg, path, tmp_err, status);
		ft_free(&path);
		return ;
	}
	result = cd_change_dir_to_valid_path(path, context->internal_pwd, status);
	if (result == FAILURE)
	{
		ft_free(&path);
		return ;
	}
	// path -> absolute path
	if (is_absolute_path(path))
		absolute_path = path;
	else
	{
		absolute_path = join_pwd_and_relative(context->internal_pwd, path);
		ft_free(&path);
	}
	cd_update_pwd(absolute_path, context);
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
