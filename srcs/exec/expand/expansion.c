#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
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

static void	expand_variables_inter(t_deque **tokens, t_context *context)
{
	expand_tokens(*tokens, context);
	remove_empty_tokens(*tokens);
	concat_tokens(*tokens);
	split_expand_word(tokens);
}

static void	expand_variables_for_redirect(t_deque *redirect_list, \
											t_context *context)
{
	t_deque_node	*list_node;
	t_redirect		*redirect;

	if (!redirect_list)
		return ;
	list_node = redirect_list->node;
	while (list_node)
	{
		redirect = (t_redirect *)list_node->content;
		if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
		{
			list_node = list_node->next;
			continue ;
		}
		expand_variables_inter(&redirect->tokens, context);
		split_expand_word(&redirect->tokens);
		list_node = list_node->next;
	}
}

// word splitting: if unquoted, word split by delimiter
t_result	expand_variables(t_ast *self_node, t_context *context)
{
	expand_variables_inter(&self_node->command, context);
	expand_variables_for_redirect(self_node->redirect_list, context);
	return (SUCCESS);
}
