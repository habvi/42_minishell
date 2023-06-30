#include "minishell.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_sys.h"

void	del_var_info(void **var_info)
{
	t_var_info	*info;

	if (!var_info || !*var_info)
		return ;
	info = (t_var_info *)*var_info;
	ft_free(&info->value);
	ft_free(&info);
	*var_info = NULL;
}

static void	set_func(t_env *env)
{
	env->is_key_exist = env_is_key_exist;
	env->get_value = env_get_value;
	env->add = env_add;
	env->join = env_join;
	env->unset = env_unset;
	env->print = env_print;
	env->print_detail = env_print_detail;
	env->clear = env_clear;
}

static void	get_environ(t_env *env)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	if (!environ)
		return ;
	while (environ[i])
	{
		env_declare_arg(environ[i], env, VAR_ENV);
		i++;
	}
}

static void	set_env_default_hash(t_env *env)
{
	env->hash = hs_create_table(ENV_LIST_SIZE, del_var_info);
	if (!env->hash)
		ft_abort();
	get_environ(env);
}

t_env	*set_default_environ(t_context *context)
{
	t_env	*env;

	env = (t_env *)x_malloc(sizeof(t_env));
	if (!env)
		ft_abort();
	context->env = env;
	set_func(env);
	set_env_default_hash(context->env);
	set_default_pwd(env);
	set_default_old_pwd(env); // todo
	return (env);
}
