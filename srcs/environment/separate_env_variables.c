#include "minishell.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_string.h"

static bool	is_only_key(const char c)
{
	return (!c);
}

// &arg[j] != NULL, len(&arg[j]) >= 0
// key guaranteed valid
// &arg[j] : "", "=foo"," or "+=bar"
static t_env_op	get_env_op(const char *const arg, size_t *j)
{
	t_env_op	op;

	if (is_only_key(arg[*j]))
		op = ENV_ADD;
	else if (arg[*j] == '=')
	{
		op = ENV_ADD;
		*j += 1;
	}
	else // +=
	{
		op = ENV_JOIN;
		*j += 2;
	}
	return (op);
}

// status
//   0: success
//   1: error
//   2: error

//  -1: malloc error
//  key is `name` ? -> !name -> status=2, return FAILURE
//      is `_`               -> status=0, return CONTINUE
static int	validate_env_key(char *key)
{
	if (!is_valid_key(key))
		return (FAILURE);
	if (ft_streq(key, "_"))
		return (CONTINUE);
	return (SUCCESS);
}

static int	free_key_ret_val(char *key, int ret_val)
{
	ft_free(key);
	return (ret_val);
}

// key=value
// key, =, value
int	separate_env_variables(const char *const arg, \
							char **key, \
							char **value, \
							t_env_op *op)
{
	size_t	i;
	int		result;

	if (dup_env_key(arg, key, &i) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	result = validate_env_key(*key);
	if (result == FAILURE)
		return (free_key_ret_val(*key, FAILURE));
	if (result == CONTINUE)
		return (free_key_ret_val(*key, CONTINUE));
	*op = get_env_op(arg, &i);
	if (dup_env_value(&arg[i], value) == PROCESS_ERROR)
		return (free_key_ret_val(*key, PROCESS_ERROR));
	return (SUCCESS);
}
