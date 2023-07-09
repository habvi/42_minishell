#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

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

// word splitting: if unquoted, word split by delimiter
t_result	expand_variables(t_ast *self_node, t_context *context)
{
	t_redirect	*redirects;

	expand_tokens(self_node->command, context);
//	split_expand_word(self_node->command);
	remove_empty_tokens(self_node->command);
	redirects = self_node->redirects;
	if (redirects)
	{
		expand_tokens(redirects->list, context);
//		split_expand_word(redirects->list);
		remove_empty_tokens(self_node->command);
	}
	return (SUCCESS);
}
