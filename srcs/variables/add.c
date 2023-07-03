#include "minishell.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_hash.h"
#include "ft_mem.h"// attr of declare is the arg_attr
// if arg_attr is NONE, use the attr of key ...(*)
//
// key    key_attr    arg_attr    declare_attr
// -------------------------------------------
// NULL    -           x           x
//                     -           -
//                     NONE        -  (*)
// !NULL   x           x           x
//                     -           -
//                     NONE        x  (*)
//         -           x           x
//                     -           -
//                     NONE        -  (*)
static t_var_attr	get_declare_attr(t_var *var, \
								const char *key, \
								t_var_attr arg_attr)
{
	t_var_attr	declare_attr;

	if (arg_attr != VAR_NONE)
		return (arg_attr);
	declare_attr = var_get_attribute(var, key);
	if (declare_attr == VAR_NONE)
		declare_attr = VAR_SHELL;
	return (declare_attr);
}

// allocate dup_key, dup_info
static char	*get_declare_value(t_var *var, \
										const char *key, \
										const char *value)
{
	char	*dup_value;

	if (value)
		dup_value = x_ft_strdup(value);
	else if (var_is_key_exist(var, key))
		dup_value = var->get_value(var, key);
	else
		dup_value = NULL;
	return (dup_value);
}

// key, var_info, op, var
// key, value, attr, op, var -> register
t_var_info	*var_create_var_info_for_add(t_var *var, \
											const char *key, \
											const char *value, \
											t_var_attr attr)
{
	t_var_info	*var_info;

	attr = get_declare_attr(var, key, attr);
	value = get_declare_value(var, key, value);
	var_info = var_create_var_info(value, attr);
	ft_free(&value);
	return (var_info);
}

void	var_add(t_var *var, const char *key, const char *value, t_var_attr attr)
{
	t_deque_node	*target;
	char			*dup_key;
	t_var_info		*var_info;

	dup_key = x_ft_strdup(key);
	var_info = var_create_var_info_for_add(var, key, value, attr);
	target = hs_find_key(var->hash, dup_key);
	if (target)
		hs_update_value(&dup_key, var_info, target, var->hash->del_hash_value);
	else
	{
		if (hs_add_to_table(var->hash, dup_key, var_info) == HASH_ERROR)
			ft_abort();
	}
}
