#include <errno.h>
#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

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
static void	validate_and_delete_old_pwd(t_var *var)
{
	char	*dup_path;

	dup_path = var->get_value(var, KEY_OLDPWD);
	if (!dup_path)
		return ;
	if (!is_valid_old_pwd(dup_path))
		var->unset(var, KEY_OLDPWD); //todo: erase t_var_info
	ft_free(&dup_path);
}

// key=OLDPWD
// value=NULL
static void	set_only_old_pwd_key(t_var *var)
{
	var_update_key_info_pair_and_add(var, KEY_OLDPWD, NULL, VAR_ENV);
}

void	set_default_old_pwd(t_var *var)
{
	if (var->is_key_exist(var, KEY_OLDPWD))
		validate_and_delete_old_pwd(var);
	set_only_old_pwd_key(var);
}
