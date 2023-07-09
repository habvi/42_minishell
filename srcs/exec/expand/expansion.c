#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

static char	*strcat_after_dollar(char *str)
{
	char	*new_str;

	new_str = x_ft_strjoin(STR_DOLLAR, str);
	ft_free(&str);
	return (new_str);
}

static char	*expand_status(char **str, t_context *context)
{
	(*str)++;
	return (x_ft_itoa(context->status));
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

static char	*substr_before_dollar(char **str)
{
	char	*head;
	char	*tail;
	char	*substr;

	head = *str;
	tail = *str;
	while (*tail && *tail != CHAR_DOLLAR)
		tail++;
	substr = x_ft_strndup(head, tail - head);
	*str = tail;
	return (substr);
}

static void	expand_token(t_token *token, t_context *context)
{
	char	*str;
	char	*new_str;
	char	*joind_str;

	joind_str = NULL;
	str = token->str;
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
	ft_free(&token->str);
	token->str = joind_str;
}

static void	expand_command(t_deque *command, t_context *context)
{
	t_deque_node	*node;
	t_token			*token;

	if (command)
	{
		node = command->node;
		while (node)
		{
			token = (t_token *)node->content;
			if (token->quote == QUOTE_SINGLE)
			{
				node = node->next;
				continue ;
			}
			expand_token(token, context);
			node = node->next;
		}
	}
}

t_result	expand_variables(t_ast *self_node, t_context *context)
{

	// parameter and variables expansion
	expand_command(self_node->command, context);
	// expand redirect
	// redirect_list = (t_deque *)self_node->redirects->list;
	// --------------
	// word splitting
	return (SUCCESS);
}
