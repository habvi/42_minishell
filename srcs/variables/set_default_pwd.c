#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"
#include "ft_string.h"

static void	update_pwd_for_double_slash(t_var *var, char **pwd_path)
{
	char	*parent_pwd;

	if (!ft_streq(*pwd_path, PATH_ROOT))
		return ;
	parent_pwd = var->get_value(var, KEY_PWD);
	if (!ft_streq(parent_pwd, "//"))
		return ;
	ft_free((void **)pwd_path);
	*pwd_path = parent_pwd;
}

void	set_default_pwd(t_var *var)
{
	char	*pwd_path;

	pwd_path = get_working_directory(SHELL_INIT);
	update_pwd_for_double_slash(var, &pwd_path);
	if (pwd_path)
	{
		var->add(var, KEY_PWD, pwd_path, VAR_ENV);
		ft_free(&pwd_path);
	}
}
