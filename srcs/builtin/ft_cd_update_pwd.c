#include "minishell.h"
#include "ms_builtin.h"
#include "ms_var.h"
#include "ft_mem.h"

static void	update_internal_pwd(char *path, t_context *context)
{
	char	*absolute_path;

	absolute_path = cd_canonicalize_path(path, context);
	ft_free(&path);
	ft_free(&context->internal_pwd);
	context->internal_pwd = absolute_path;
}

static t_var_attr	get_attr_and_unset_if_newvalue_null(t_var *var)
{
	t_var_attr	attr;
	char		*value;

	attr = var_get_attribute(var, KEY_OLDPWD);
	value = var_get_value(var, KEY_PWD);
	if (!value)
		var->unset(var, KEY_OLDPWD);
	ft_free(&value);
	return (attr);
}

static void	update_var_pwd_oldpwd(t_context *context)
{
	t_var		*var;
	t_var_attr	oldpwd_attr;
	char		*new_old_pwd;
	char		*new_pwd;

	var = context->var;
	new_old_pwd = var_get_value(var, KEY_PWD);
	new_pwd = context->internal_pwd;

	oldpwd_attr = get_attr_and_unset_if_newvalue_null(var);
	update_pwd_in_cd(var, KEY_OLDPWD, new_old_pwd, oldpwd_attr);
	update_pwd_in_cd(var, KEY_PWD, new_pwd, VAR_NONE);
	ft_free(&new_old_pwd);
}

void	cd_update_pwd(char *path, t_context *context)
{
	update_internal_pwd(path, context);
	update_var_pwd_oldpwd(context);
}
