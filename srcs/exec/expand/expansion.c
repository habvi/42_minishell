#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

static char	*strcat_after_doller(char *str)
{
	char	*new_str;

	new_str = x_ft_strjoin("$", str);
	ft_free(&str);
	return (new_str);
}

// $_aaaa, alnum or _
// $_&
// $_\0
// $, $8, $$
static char	*find_key_and_substr(char **str, t_context *context)
{
	char	*head;
	char	*tail;
	char	*substr;
	char	*value;
	t_var	*var;

	(*str)++;
	if (**str == '?')
	{
		(*str)++;
		return (x_ft_itoa(context->status));
	}
	head = *str;
	tail = *str;
	if (!is_valid_head(*head))
		return (strcat_after_doller(x_ft_strdup("")));
	tail++;
	while (tail && is_valid_after_head(*tail))
		tail++;
	*str = tail;
	substr = x_ft_strndup(head, tail - head);
	ft_dprintf(2, "4 [%s]\n", substr);
	if (ft_streq(substr, "_"))
	{
		(*str)++;
		return (strcat_after_doller(substr));
	}
	var = context->var;
	value = var->get_value(var, substr);
	ft_free(&substr);
	return (value);
}

static char	*substr_before_doller(char **str)
{
	char	*head;
	char	*tail;
	char	*substr;

	head = *str;
	tail = *str;
	while (*tail && *tail != '$')
		tail++;
	substr = x_ft_strndup(head, tail - head);
	*str = tail;
	return (substr);
}

static void	expand_str(t_token *token, t_context *context)
{
	char	*str;
	char	*new_str;
	char	*tmp;
	char	*joind_str;

	joind_str = NULL;
	str = token->str;
	while (*str)
	{
		ft_dprintf(2, "1 [%s]\n", str);
		if (*str == '$')
		{
			new_str = find_key_and_substr(&str, context);
			tmp = joind_str;
			joind_str = x_ft_strjoin(tmp, new_str);
			ft_dprintf(2, "2 [%s]\n", joind_str);
			ft_free(&tmp);
			ft_free(&new_str);
		}
		new_str = substr_before_doller(&str);
		tmp = joind_str;
		joind_str = x_ft_strjoin(tmp, new_str);
		ft_dprintf(2, "3 [%s]\n", joind_str);
		ft_free(&tmp);
		ft_free(&new_str);
	}
	ft_free(&token->str);
	token->str = joind_str;
}

t_result	expand_variables(t_ast *self_node, t_context *context)
{
	t_deque			*command;
	t_deque_node	*node;
	t_token			*token;

	// parameter and variables expansion
	// expand command
	command = (t_deque *)self_node->command;
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
			expand_str(token, context);
			node = node->next;
		}
	}
	// expand redirect
	// redirect_list = (t_deque *)self_node->redirects->list;
	// --------------
	// word splitting
	return (SUCCESS);
}
