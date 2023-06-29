#include "minishell.h"
#include "ft_hash.h"
#include "ft_mem.h"
#include "ft_sys.h"

static void	del_env_val(void *value)
{
	char	*val;

	val = value;
	ft_free(&val);
}

static void	set_func(t_env *env)
{
	env->is_key_exist = env_is_key_exist;
	env->get_value = env_get_value;
	env->set = env_set;
	env->unset = env_unset;
	env->print = env_print;
	env->print_detail = env_print_detail;
	env->clear = env_clear;
}

static void	set_environ_to_hash(t_context *context)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	if (!environ)
		return ;
	while (environ[i])
	{
		env_init_declare_arg(environ[i], context);
		i++;
	}
}

static void	set_env_default_hash(t_context *context)
{
	t_env	*env;

	env = context->env;
	env->hash = hs_create_table(ENV_LIST_SIZE, del_env_val);
	if (!env->hash)
		ft_abort();
	set_environ_to_hash(context);
}

t_env	*init_environ(t_context *context)
{
	t_env	*env;

	env = (t_env *)x_malloc(sizeof(t_env));
	if (!env)
		ft_abort();
	context->env = env;
	set_func(env);
	set_env_default_hash(context);
	init_pwd(env);
	init_old_pwd(env);
	return (env);
}
