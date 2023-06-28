#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_dprintf.h"
#include "ft_string.h"
#include "ft_mem.h"

static char	*get_value_for_cd(t_env *env, const char *key)
{
	char	*value;

	if (env->is_key_exist(env, key))
		value = env->get_value(env, key);
	else
		value = NULL;
	return (value);
}

// "~"  -> HOME
// "-"  -> OLDPWD
// else -> arg
static char	*set_path_by_arg(const char *arg, t_env *env)
{
	char	*path;

	if (ft_streq(arg, CD_ARG_HOME)) // ~  		// NULL
		path = get_value_for_cd(env, KEY_HOME);
	else if (ft_streq(arg, CD_ARG_OLDPWD)) // -  	// NULL
		path = get_value_for_cd(env, KEY_OLDPWD);
	else
	{
		path = ft_strdup(arg);
		if (!path)
			ft_abort();
	}
	return (path);
}

//  arg                       bash                         minishell
// unset HOME; cd <no arg>   path=NULL; HOME not set
// unset HOME; cd ~          getpath from /etc/passwd   (tmp) same as <no arg>
// -> unset OLD ;cd -        path=NULL; OLDPWD not set
static char	*set_cd_path(const char *arg, t_env *env)
{
	char	*path;

	if (!arg)
		path = get_value_for_cd(env, KEY_HOME);
	else
		path = set_path_by_arg(arg, env);
	return (path);
}

static bool	is_valid_cd_path(char *path, int *tmp_err)
{
	if (!path)
		return (false);
	if (!test_opendir(path, tmp_err))
		return (false);
	return (true);
}

static void	cd_to_valid_path(char *path, t_context *context)
{
	(void)path;
	(void)context;
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

// arg
// NULL   : home
// -      : OLDPWD
// ~      : home
// others : path
static void	change_directory(const char *arg, \
								t_context *context, \
								uint8_t *status)
{
	char	*path;
	int		tmp_err;

	path = set_cd_path(arg, context->env);
	if (!is_valid_cd_path(path, &tmp_err))
	{
		print_err_set_status(arg, path, tmp_err, status);
		ft_free(&path);
		return ;
	}
	cd_to_valid_path(path, context);
	// cd success
	free(context->internal_old_pwd);
	context->internal_old_pwd = context->internal_pwd;
	context->internal_pwd = path;
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
