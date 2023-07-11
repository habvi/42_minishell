#include "minishell.h"
#include "ms_builtin.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_mem.h"

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

static void	expand_tokens(t_deque *tokens, t_context *context)
{
	t_deque_node	*node;
	t_token			*token;

	if (tokens)
	{
		node = tokens->node;
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

static bool	is_assignment_command(t_deque *tokens)
{
	t_token	*token;

	token = (t_token *)tokens->node;
	if (!token)
		return (false);
	if (ft_streq(token->str, CMD_DECLARE))
		return (true);
	if (ft_streq(token->str, CMD_EXPORT))
		return (true);
	return (false);
}

void	expand_variables_inter(t_deque **tokens, t_context *context)
{
	bool	is_assign_cmd;

	is_assign_cmd = is_assignment_command(*tokens);
	expand_tokens(*tokens, context);
	remove_empty_tokens(*tokens);
	concat_tokens(*tokens);
	split_expand_word(tokens, is_assign_cmd);
}

// word splitting: if unquoted, word split by delimiter
t_result	expand_variables(t_ast *self_node, t_context *context)
{
	t_redirect	*redirects;

	expand_variables_inter(&self_node->command, context);
	redirects = self_node->redirects;
	if (redirects)
		expand_variables_inter(&redirects->list, context);
	return (SUCCESS);
}
