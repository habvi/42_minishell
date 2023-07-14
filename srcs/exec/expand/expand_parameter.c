#include "minishell.h"
#include "ms_expansion.h"
#include "ms_var.h"
#include "ft_mem.h"
#include "ft_string.h"

static char	*expand_status(char **str, t_context *context)
{
	(*str)++;
	return (x_ft_itoa(context->status));
}

static char	*strcat_after_dollar(char *str)
{
	char	*new_str;

	new_str = x_ft_strjoin(STR_DOLLAR, str);
	ft_free(&str);
	return (new_str);
}

static char	*expand_key(char **str, t_var *var)
{
	char	*head;
	char	*tail;
	char	*key;
	char	*value;

	head = *str;
	tail = *str;
	if (!is_valid_head(*head))
		return (x_ft_strdup(STR_DOLLAR));
	tail++;
	while (tail && is_valid_after_head(*tail))
		tail++;
	*str = tail;
	key = x_ft_strndup(head, tail - head);
	if (ft_streq(key, STR_UNDERSCORE))
	{
		(*str)++;
		return (strcat_after_dollar(key));
	}
	value = var->get_value(var, key);
	ft_free(&key);
	return (value);
}

// $_aaaa, alnum or _
// $_&
// $_\0
// $, $8, $$
static char	*expand_parameter(char **str, t_context *context)
{
	char	*value;

	(*str)++;
	if (**str == PARAM_STATUS)
		value = expand_status(str, context);
	else
		value = expand_key(str, context->var);
	return (value);
}

char	*get_expand_token_str(char *str, t_context *context)
{
	char	*new_str;
	char	*joind_str;

	joind_str = NULL;
	while (*str)
	{
		if (*str == CHAR_DOLLAR)
		{
			new_str = expand_parameter(&str, context);
			joind_str = extend_str(joind_str, new_str);
		}
		new_str = substr_before_dollar(&str);
		joind_str = extend_str(joind_str, new_str);
	}
	return (joind_str);
}
