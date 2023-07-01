#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"

void	set_default_pwd(t_env *env)
{
	char	*pwd_path;

	pwd_path = get_working_directory(SHELL_INIT);
	if (pwd_path == NULL)
		env->unset(env, KEY_PWD);
	else
	{
		env_create_info_add(env, KEY_PWD, pwd_path, VAR_ENV);
		ft_free(&pwd_path);
	}
	return ;
}
