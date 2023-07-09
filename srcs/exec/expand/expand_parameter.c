#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
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
char	*expand_parameter(char **str, t_context *context)
{
	char	*value;

	(*str)++;
	if (**str == PARAM_STATUS)
		value = expand_status(str, context);
	else
		value = expand_key(str, context->var);
	return (value);
}
