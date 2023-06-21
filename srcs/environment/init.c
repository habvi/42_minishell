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
	env->set = set;
	env->append = append;
	env->get_value = get_value;
	env->unset = unset;
	env->print_env = print_env;
	env->print_export = print_export;
}

static int	get_environ(t_env *env)
{
	extern char	**environ;

	// todo

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
