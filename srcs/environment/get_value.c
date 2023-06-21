#include "minishell.h"
#include "ft_hash.h"

// return value of key
// if key not found or value is NULL, returns empty string ...?

//  return value need allocate ...?
//  use case : expansion, etc.
char	*env_get_value(t_env *env, char *key)
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
