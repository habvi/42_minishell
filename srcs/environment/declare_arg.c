#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

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

static t_result	separate_env_variables(const char *const arg, \
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

// all malloc ?
// key=value -> key, = ,value, attr
t_var_info	*env_create_var_info(const char *value, t_var_attr attr)
{
	t_var_info	*info;

	info = (t_var_info *)x_malloc(sizeof(t_var_info));
	if (!info)
		ft_abort();
	info->value = value;
	info->attr = attr;
	return (info);
}

// arg: key=value
t_result	env_declare_arg(const char *const arg, t_env *env, t_var_attr attr)
{
	t_result	result;
	char		*key;
	char		*value;
	t_var_info	*var_info;
	t_env_op	op;

	result = separate_env_variables(arg, &key, &value, &op);
	if (result == FAILURE || result == CONTINUE)
		return (result);
	var_info = env_create_var_info(value, attr); // todo: value, attr -> t_var_info
	env->set(env, key, var_info, op);
	return (result);
}

// k, v, attr, env, op
// if (op == ADD)
//   env->add
// else
//   env->join
//
