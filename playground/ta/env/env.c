#include "env.h"
#include "ft_mem.h"
#include "ft_string.h"

// 1. environ -> hash
// 2. command env, export, unset

// env[i]:PATH="/bin:/usr/bin"
//  char *key = PATH
//  char *value = /bin:/usr/bin

// env.list_env	-> env
// env.list_all	-> export
// env.set		-> export
// env.get		-> expansion
// env.del		-> unset

// key expected `name` -> void ...?
int	set(t_var *env, char *key, char *value)
{
	// strdup key, value
	// set to hash
	if (hs_set_key(env->hash, key, value) == HASH_ERROR)
		return (FAILURE); // todo: hs_clear();
	return (SUCCESS);
}

// key expected `name` -> void ...?
int	append(t_var *env, char *key, char *value)
{
	// strdup key, value
	// set to hash
	if (hs_set_key(env->hash, key, value) == HASH_ERROR)
		return (FAILURE); // todo: hs_clear();
	return (SUCCESS);
}

// unset failure case ...? void ?
int	unset(t_var *env, char *key)
{
	t_deque_node	*node;

	node = hs_find_key(env->hash, (const char *)key);
	if (!node)
		return (SUCCESS);


	return (SUCCESS);
}

// return value of key
// if key not found or value is NULL, returns empty string ...?

//  return value need allocate ...?
//  use case : expansion, etc.
char	*get(t_var *env, char *key)
{
	char	*value;
	char	*duped_value;

	value = hs_get_value(env->hash, key);
	if (!value)
		value = "";
	duped_value = ft_strdup(value);
	if (!duped_value)
		return (NULL); // todo: hs_clear();
	return (duped_value);
}

void	list(t_var *env)
{
	// print key-value-pairs to stdout
	//   except only key
	//   `key=value\n`
}

void	list_all(t_var *env)
{
	// print key-value-pairs to stdout
	//   include only key
	//   `declare -x key="value\n`
}

void	del_value(void *value)
{
	ft_free(&value);
}

int	init_env(t_var *env)
{
	if (!env)
		return (FAILURE);
	env->set = set;
	env->append = append;
	env->unset = unset;
	env->get = get;
	env->list = list_all;
	env->list = list_all;
	env->del_value = del_value;
	env->hash = hs_create_table(LIST_SIZE, env->del_value);
	if (!env->hash)
		return (FAILURE);
	return (SUCCESS);
}

int	get_environ(t_var *env)
{
	extern char *environ;

	if (!env)
		return (FAILURE);

	// environ -> hash
	//  `key`=`value`

	return (SUCCESS);
}

int	main(void)
{
	t_var	env;

	// init
	if (init_env(&env) == FAILURE)
		return (1);
	if (get_environ(&env) == FAILURE)
		return (1);

	// test
	// list
	env.list(&env);

	// list_all
	env.list_all(&env);

	// set
	env.set(&env, "key1", "value1");
	env.set(&env, "key2", "value2");
	env.list_all(&env);

	// unset
	env.unset(&env, "key2");
	env.list_all(&env);

	return (0);
}