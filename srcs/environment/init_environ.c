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
	env->is_key_exist = is_key_exist;
	env->get_value = env_get_value;
	env->set = env_set;
	env->unset = env_unset;
	env->print = env_print;
	env->print_detail = env_print_detail;
}

// if init_environ() -> declare_arg() returns FAILURE, nothing happen & skip.
static void	get_environ(t_env *env)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	if (!environ)
		return ;
	while (environ[i])
	{
		declare_arg(environ[i], env);
		i++;
	}
}

static void	set_hash(t_env *env)
{
	env->hash = hs_create_table(ENV_LIST_SIZE, del_env_val);
	if (!env->hash)
		ft_abort();
	get_environ(env);
}

t_env	*init_environ(void)
{
	t_env	*env;

	env = (t_env *)x_malloc(sizeof(t_env));
	if (!env)
		ft_abort();
	set_func(env);
	set_hash(env);
	return (env);
}
