#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

static bool	is_valid_old_pwd_path(const char *path, t_result *result)
{
	int	tmp_err;

	return (is_valid_path(path, &tmp_err, result));
}

// key=OLDPWD
// value=NULL
static void	set_old_pwd_key_only(t_var *var)
{
	var->add(var, KEY_OLDPWD, NULL, VAR_ENV);
}

// search path && is invalid directory
// delete OLDPWD in hash
static t_result	check_and_rm_invalid_oldpwd_path(t_var *var)
{
	char		*dup_path;
	t_result	result;

	dup_path = var->get_value(var, KEY_OLDPWD);
	if (!dup_path)
		return (FAILURE);
	if (!is_valid_old_pwd_path(dup_path, &result))
	{
		if (result == PROCESS_ERROR)
		{
			ft_free((void **)&dup_path);
			return (PROCESS_ERROR);
		}
		var->unset(var, KEY_OLDPWD);
		set_old_pwd_key_only(var);
	}
	ft_free((void **)&dup_path);
	return (result);
}

t_result	set_default_old_pwd(t_var *var)
{
	t_result	result;

	result = SUCCESS;
	if (var->is_key_exist(var, KEY_OLDPWD))
		result = check_and_rm_invalid_oldpwd_path(var);
	else
		set_old_pwd_key_only(var);
	return (result);
}
