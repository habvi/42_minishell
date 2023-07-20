#include "ms_expansion.h"
#include "ms_parse.h"
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

	if (!tokens)
		return ;
	node = tokens->node;
	while (node)
	{
		token = (t_token *)node->content;
		if (token->quote == QUOTE_SINGLE || !ft_strchr(token->str, CHAR_DOLLAR))
		{
			node = node->next;
			continue ;
		}
		expand_token(token, context);
		node = node->next;
	}
}

t_result	expand_processing(t_deque **tokens, t_context *context)
{
	t_result	result;

	expand_tokens(*tokens, context);
	split_expand_word(tokens);
	concat_tokens(*tokens);
	remove_empty_tokens(*tokens);
	result = expand_wildcard(tokens);
	return (result);
}

// word splitting: if unquoted, word split by delimiter
t_result	expand_variable_of_cmd_tokens(t_ast *self_node, t_context *context)
{
	return (expand_processing(&self_node->command, context));
}
