#include "minishell.h"
#include "ft_mem.h"
#include "ft_string.h"

char	*swap_pwd_value(char *value, const char *new_value)
{
	char	*dup_value;

	ft_free(&value);
	if (!new_value)
		return (NULL);
	dup_value = ft_strdup(new_value);
	if (!dup_value)
		ft_abort();
	return (dup_value);
}

// key is PWD/OLDPWD, get value from internal
char	*update_pwd_by_internal(const char *key, \
								char *value, \
								t_context *context)
{
	char	*new_value;

	if (ft_streq(key, KEY_PWD))
		new_value = swap_pwd_value(value, context->internal_pwd);
	else if (ft_streq(key, KEY_OLDPWD))
		new_value = swap_pwd_value(value, context->internal_old_pwd);
	else
		new_value = value;
	return (new_value);
}
