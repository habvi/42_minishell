#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_string.h"

#include "ft_dprintf.h"

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

// ft_cd の cd_update_pwd() の最後と共通化できそう
// PWD が unset されたかという情報を t_env で持ってないとだめ…？ cd されたら unset=off
t_result	env_declare_arg(const char *const arg, t_context *context)
{
	t_result	result;
	char		*key;
	char		*value;
	t_env_op	op;
	t_env		*env;
	bool		is_key_pwd_unset; 
	bool		is_key_old_pwd_unset; 

	// ft_dprintf(2, "\ninter_pwd    : %s\n", context->internal_pwd);
	// ft_dprintf(2, "inter_old_pwd: %s\n", context->internal_old_pwd);
	env = context->env;
	is_key_pwd_unset = !env->is_key_exist(env, KEY_PWD);
	is_key_old_pwd_unset = !env->is_key_exist(env, KEY_OLDPWD);

	// set env
	result = separate_env_variables(arg, &key, &value, &op);
	if (result == FAILURE || result == CONTINUE)
		return (result);
	env_set_dup_key_value(env, key, value, op);

	if (value)
	{
		if (!is_key_pwd_unset && ft_streq(key, KEY_PWD))
			context->internal_pwd = value;
		else if (!is_key_old_pwd_unset && ft_streq(key, KEY_OLDPWD))
			context->internal_old_pwd = value;
		else
			ft_free(&value);
		ft_free(&key);
	}
	else
	{
		if (!is_key_pwd_unset && ft_streq(key, KEY_PWD))
			env_set_dup_key_value(env, KEY_PWD, context->internal_pwd, op);
		else if (!is_key_old_pwd_unset && ft_streq(key, KEY_OLDPWD))
			env_set_dup_key_value(env, KEY_OLDPWD, context->internal_old_pwd, op);
		ft_free(&key);
		ft_free(&value);
	}
	// ft_dprintf(2, "\ninter_pwd    : %s\n", context->internal_pwd);
	// ft_dprintf(2, "inter_old_pwd: %s\n\n", context->internal_old_pwd);

	// if (ft_streq(key, KEY_PWD))
	// 	value = swap_pwd_value(value, context->internal_pwd);
	// if (ft_streq(key, KEY_OLDPWD))
	// 	value = swap_pwd_value(value, context->internal_old_pwd);
	// env_set_dup_key_value(context->env, key, value, op);
	// ft_free(&key);
	// ft_free(&value);
	return (result);
}

t_result	env_init_declare_arg(const char *const arg, t_context *context)
{
	t_result	result;
	char		*key;
	char		*value;
	t_env_op	op;

	result = separate_env_variables(arg, &key, &value, &op);
	if (result == FAILURE || result == CONTINUE)
		return (result);
	env_set_dup_key_value(context->env, key, value, op);
	ft_free(&key);
	ft_free(&value);
	return (result);
}


/*

cd ->   inter
         ↓ ↑
         env   <-  export

unset : erase env

*/