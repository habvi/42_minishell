#include "minishell.h"
#include "ms_builtin.h"
#include "ft_string.h"

// "~"  -> HOME
// "-"  -> OLDPWD
// else -> arg
static char	*set_path_by_arg(const char *arg, t_env *env)
{
	char	*path;

	if (ft_streq(arg, CD_ARG_HOME)) // ~  		// NULL
		path = env->get_value(env, KEY_HOME);
	else if (ft_streq(arg, CD_ARG_OLDPWD)) // -  	// NULL
		path = env->get_value(env, KEY_OLDPWD);
	else
	{
		path = ft_strdup(arg);
		if (!path)
			ft_abort();
	}
	return (path);
}

//  arg                       bash                         minishell
// unset HOME; cd <no arg>   path=NULL; HOME not set
// unset HOME; cd ~          getpath from /etc/passwd   (tmp) same as <no arg>
// -> unset OLD ;cd -        path=NULL; OLDPWD not set
char	*cd_set_path(const char *arg, t_env *env)
{
	char	*path;

	if (!arg)
		path = env->get_value(env, KEY_HOME);
	else
		path = set_path_by_arg(arg, env);
	return (path);
}
