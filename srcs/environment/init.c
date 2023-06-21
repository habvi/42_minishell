#include "minishell.h"
#include "ft_hash.h"
#include "ft_mem.h"

static void	del_env_val(void *value)
{
	char	*val;

	val = value;
	ft_free(val);
}

static void	set_func(t_env *env)
{
	env->set = env_set;
	env->append = env_append;
	env->get_value = env_get_value;
	env->unset = env_unset;
	env->print = env_print;
	env->print_detail = env_print_detail;
}

static int	get_environ(t_env *env)
{
	extern char	**environ;

	// todo
	(void)env;
	(void)environ;
	return (SUCCESS);
}

static int	set_hash(t_env *env)
{
	if (!env)
		return (FAILURE);
	env->hash = hs_create_table(ENV_LIST_SIZE, del_env_val);
	if (!env->hash)
		return (FAILURE);

	if (get_environ(env) == FAILURE)
	{
		hs_clear(&env->hash);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	init_environ(t_env *env)
{
	set_func(env);

	if (set_hash(env) == FAILURE)
		return (FAILURE);

	return (SUCCESS);
}
