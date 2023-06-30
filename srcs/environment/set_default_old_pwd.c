#include <dirent.h>
#include <errno.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_string.h"

// static bool	is_invalid_directory_path(int tmp_err)
// {
// 	if (tmp_err == 0)
// 		return (false);
// 	if (tmp_err == EACCES)
// 		return (false);
// 	return (true);
// }

// search path && is invalid directory
// delete OLDPWD in hash
// static void	validate_and_delete_old_pwd(t_env *env)
// {
// 	char	*dup_path;
// 	int		tmp_err;
// 	DIR		*dirp;

// 	dup_path = env->get_value(env, KEY_OLDPWD);
// 	errno = 0;
// 	dirp = opendir((const char *)dup_path);
// 	tmp_err = errno;
// 	if (is_invalid_directory_path(tmp_err))
// 		env->unset(env, KEY_OLDPWD);
// 	closedir(dirp);
// 	ft_free(&dup_path);
// }

// key=OLDPWD
// value=NULL
// static void	set_only_old_pwd_key(t_env *env)
// {
// 	char	*dup_key;

// 	dup_key = ft_strdup(KEY_OLDPWD);
// 	if (!dup_key)
// 		ft_abort();
// 	env->add(env, dup_key, NULL);
// }

void	set_default_old_pwd(t_env *env)
{
	(void)env;
	// if (env->is_key_exist(env, KEY_OLDPWD))
	// 	validate_and_delete_old_pwd(env);
	// else
	// 	set_only_old_pwd_key(env);
	return ;
}
