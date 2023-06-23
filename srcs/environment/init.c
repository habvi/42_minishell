#include "minishell.h"
#include "ft_hash.h"
#include "ft_mem.h"

// erase
#include "ft_string.h"
#include "ft_dprintf.h"
#include <stdlib.h>

static void	del_env_val(void *value)
{
	char	*val;

	val = value;
	ft_free(val);
}

static void	set_func(t_env *env)
{
	env->set = env_set;
	env->get_value = env_get_value;
	env->unset = env_unset;
	env->print = env_print;
	env->print_detail = env_print_detail;
}

static int	get_environ(t_env *env)
{
	extern char	**environ;

	// todo
	(void)environ;
	(void)env;
	// hs_add_to_table
	// erase
//	hs_set_key(env->hash, ft_strdup("key_1"), ft_strdup("val_1"));
//	hs_set_key(env->hash, ft_strdup("key_2"), ft_strdup("val_2"));
//	hs_set_key(env->hash, ft_strdup("key_3"), ft_strdup("val_3"));
//	hs_set_key(env->hash, ft_strdup("key_4"), ft_strdup("val_4"));
	return (SUCCESS);
}

// erase
//static void	display_elem(void *content)
//{
//	t_elem	*elem;
//
//	if (!content)
//		return ;
//	elem = content;
//	ft_dprintf(STDERR_FILENO, "[\"%s\", \"%s\"]",
//	elem->key, (char *)elem->value);
//}

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
//	hs_display(env->hash, display_elem); // erase
	return (SUCCESS);
}

t_env	*init_environ(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	set_func(env);
	if (set_hash(env) == FAILURE)
		return (NULL);
	return (env);
}
