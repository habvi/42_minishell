#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

void	init_pwd(t_env *env)
{
	char	*pwd;
	char	*dup_key;

	pwd = get_working_directory(SHELL_INIT);
	if (pwd == NULL)
		env->unset(env, PWD);
	else
	{
		dup_key = ft_strdup(PWD);
		if (!dup_key)
			ft_abort();
		if (!pwd)
			ft_abort();
		env->set(env, dup_key, pwd, ENV_ADD);
	}
}
