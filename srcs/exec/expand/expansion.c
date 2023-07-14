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
	char	*expand_str;

	expand_str = get_expand_token_str(token->str, context);
	ft_free(&token->str);
	token->str = expand_str;
	set_is_quoted_value_to_arr(token);
}

static void	expand_tokens(const t_deque *tokens, t_context *context)
{
	t_deque_node	*node;
	t_token			*token;

	if (tokens)
	{
		node = tokens->node;
		while (node)
		{
			token = (t_token *)node->content;
			if (token->quote == QUOTE_SINGLE \
			|| !ft_strchr(token->str, CHAR_DOLLAR))
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
//	debug_token_dq(*tokens, "before expand");
//	ft_dprintf(2, "1 tokens:%p\n", *tokens);
	expand_tokens(*tokens, context);
//	debug_token_dq(*tokens, "after expand");
	split_expand_word(tokens);
//	debug_token_dq(*tokens, "after split");
	concat_tokens(*tokens);
	remove_empty_tokens(*tokens);
//	debug_token_dq(*tokens, "after remove");
	expand_wildcard(tokens);
	// debug_token_dq(*tokens, "after wild");
}

static t_result	expand_variables_for_redirect(t_deque *redirect_list, \
												t_context *context)
{
	t_deque_node	*list_node;
	t_redirect		*redirect;
	t_result		result;

	if (!redirect_list)
		return (SUCCESS);
	list_node = redirect_list->node;
	while (list_node)
	{
		redirect = (t_redirect *)list_node->content;
		if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
		{
			result = expand_for_heredoc(redirect, context);
			if (result == PROCESS_ERROR)
				return (PROCESS_ERROR);
			list_node = list_node->next;
			continue ;
		}
		expand_variables_inter(&redirect->tokens, context);
		split_expand_word(&redirect->tokens);
		list_node = list_node->next;
	}
	return (SUCCESS);
}

// word splitting: if unquoted, word split by delimiter
t_result	expand_variables(t_ast *self_node, t_context *context)
{
	t_result	result;

	result = SUCCESS;
	expand_variables_inter(&self_node->command, context);
	result = expand_variables_for_redirect(self_node->redirect_list, context);
	return (result);
}
