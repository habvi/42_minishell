#include <errno.h>
#include <dirent.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"
#include "ft_mem.h"

static bool	is_invalid_directory_path(int tmp_errno)
{
	if (tmp_errno == 0)
		return (false);
	if (tmp_errno == EACCES)
		return (false);
	return (true);
}

// search path && is invalid directory
// delete OLDPWD in hash
static void	validate_and_delete_old_pwd(t_env *env)
{
	char	*dup_path;
	int		tmp_errno;
	DIR		*dirp;

	dup_path = env->get_value(env, OLDPWD);
	errno = 0;
	dirp = opendir((const char *)dup_path);
	(void)dirp;
	tmp_errno = errno;
	if (is_invalid_directory_path(tmp_errno))
		env->unset(env, OLDPWD);
	closedir(dirp);
	ft_free(&dup_path);
}

// key=OLDPWD
// value=NULL
static void	set_only_old_pwd_key(t_env *env)
{
	char	*dup_key;

	dup_key = ft_strdup(OLDPWD);
	if (!dup_key)
		ft_abort();
	env->set(env, dup_key, NULL, ENV_ADD);
}

static char	*get_old_pwd(t_env *env)
{
	if (env->is_key_exist(env, OLDPWD))
		validate_and_delete_old_pwd(env);
	else
		set_only_old_pwd_key(env);
	return (NULL);
}

void	init_old_pwd(t_params *params)
{
	params->old_pwd = get_old_pwd(params->env);
}
