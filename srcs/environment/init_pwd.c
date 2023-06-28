#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

void	init_pwd(t_env *env)
{
	char	*pwd_path;
	char	*dup_key;

	pwd_path = get_working_directory(SHELL_INIT);
	if (pwd_path == NULL)
		env->unset(env, KEY_PWD);
	else
	{
		dup_key = ft_strdup(KEY_PWD);
		if (!dup_key)
			ft_abort();
		if (!pwd_path)
			ft_abort();
		env->set(env, dup_key, pwd_path, ENV_ADD);
	}
}
