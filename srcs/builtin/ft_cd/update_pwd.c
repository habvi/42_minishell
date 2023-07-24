#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

static void	update_internal_pwd(char *absolute_path, t_context *context)
{
	ft_free((void **)&context->internal_pwd);
	context->internal_pwd = absolute_path;
}

static void	set_condition_old_pwd_for_update(t_var *var)
{
	char		*new_old_pwd;

	new_old_pwd = var_get_value(var, KEY_PWD);
	if (!new_old_pwd)
		var->unset(var, KEY_OLDPWD);
	ft_free((void **)&new_old_pwd);
}

static void	update_var_old_pwd(t_var *var)
{
	char		*new_old_pwd;
	t_var_attr	new_old_pwd_attr;

	new_old_pwd = var_get_value(var, KEY_PWD);
	new_old_pwd_attr = var_get_attribute(var, KEY_OLDPWD);
	set_condition_old_pwd_for_update(var);
	var->add(var, KEY_OLDPWD, new_old_pwd, new_old_pwd_attr);
	ft_free((void **)&new_old_pwd);
}

static void	update_var_pwd(t_context *context)
{
	t_var		*var;
	char		*new_pwd;

	var = context->var;
	new_pwd = context->internal_pwd;
	var->add(var, KEY_PWD, new_pwd, VAR_NONE);
}

void	cd_update_pwd(char *path, t_context *context)
{
	update_internal_pwd(path, context);
	update_var_old_pwd(context->var);
	update_var_pwd(context);
}
