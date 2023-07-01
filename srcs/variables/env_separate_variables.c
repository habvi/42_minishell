#include "minishell.h"
#include "ms_var.h"
#include "ft_mem.h"
#include "ft_string.h"

static bool	is_only_key(const char c)
{
	return (!c);
}

// &arg[j] != NULL, len(&arg[j]) >= 0
// key guaranteed valid
// &arg[j] : "", "=", "value", ""=value", "+=", "+=value"
static t_env_op	get_env_op(const char *const arg, size_t *i)
{
	t_env_op	op;

	if (is_only_key(arg[*i]))
		op = ENV_ADD;
	else if (arg[*i] == '=')
	{
		op = ENV_ADD;
		*i += 1;
	}
	else // +=
	{
		op = ENV_JOIN;
		*i += 2;
	}
	return (op);
}

//  key is `name` ? -> true : status=0, return SUCCESS(0)
//                     false: status=2, return FAILURE(1)
//      is `_`      ->        status=0, return CONTINUE(2)
static t_result	validate_env_key(char *key)
{
	if (!is_valid_key(key))
		return (FAILURE);
	if (ft_streq(key, "_"))
		return (CONTINUE);
	return (SUCCESS);
}

// arg           key  value  op(enum)
// ---------------------------------
// key=value  -> key  value  =  (ADD)
// key=       -> key  ""     =  (ADD)
// key+=value -> key  value  += (JOIN)
// key+=      -> key  ""     += (JOIN)
// key        -> key  NULL      (ADD)
t_result	separate_env_variables(const char *const arg, \
									char **key, \
									char **value, \
									t_env_op *op)
{
	size_t		i;
	t_result	result;

	*key = dup_env_key(arg, &i);
	result = validate_env_key(*key);
	if (result == FAILURE || result == CONTINUE)
	{
		ft_free(key);
		return (result);
	}
	*op = get_env_op(arg, &i);
	*value = dup_env_value(&arg[i]);
	return (result);
}
