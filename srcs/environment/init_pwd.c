#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"

void	init_pwd(t_env *env)
{
	char	*pwd_path;

	pwd_path = get_working_directory(SHELL_INIT);
	if (pwd_path == NULL)
		env->unset(env, KEY_PWD);
	else
	{
		env_set_dup_key_value(env, KEY_PWD, pwd_path, ENV_ADD);
		ft_free(&pwd_path);
	}
}
