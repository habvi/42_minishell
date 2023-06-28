#include <errno.h>
#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_string.h"

static bool	is_permission_denied(int tmp_err)
{
	return (tmp_err == EACCES);
}

static bool	is_valid_old_pwd(const char *path)
{
	int		tmp_err;

	if (test_opendir(path, &tmp_err))
		return (true);
	if (is_permission_denied(tmp_err))
		return (true);
	return (false);
}

// search path && is invalid directory
// delete OLDPWD in hash
static void	validate_and_delete_old_pwd(t_env *env)
{
	char	*dup_path;

	dup_path = env->get_value(env, KEY_OLDPWD);
	if (!is_valid_old_pwd(dup_path))
		env->unset(env, KEY_OLDPWD);
	ft_free(&dup_path);
}

// key=OLDPWD
// value=NULL
static void	set_only_old_pwd_key(t_env *env)
{
	char	*dup_key;

	dup_key = ft_strdup(KEY_OLDPWD);
	if (!dup_key)
		ft_abort();
	env->set(env, dup_key, NULL, ENV_ADD);
}

void	init_old_pwd(t_env *env)
{
	if (env->is_key_exist(env, KEY_OLDPWD))
		validate_and_delete_old_pwd(env);
	else
		set_only_old_pwd_key(env);
}
