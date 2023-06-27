#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

void	init_pwd(char **pwd, t_env *env)
{
	char	*dup_key;
	char	*dup_value;

	*pwd = get_working_directory(SHELL_INIT);
	if (*pwd == NULL)
		env->unset(env, PWD);
	else
	{
		dup_key = ft_strdup(PWD);
		if (!dup_key)
			ft_abort();
		dup_value = ft_strdup(*pwd);
		if (!dup_value)
			ft_abort();
		env->set(env, dup_key, dup_value, ENV_ADD);
	}
}
