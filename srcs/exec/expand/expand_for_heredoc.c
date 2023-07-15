#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"

static bool	is_expand_in_heredoc(t_redirect *redirect)
{
	t_token	*token;

	token = (t_token *)redirect->tokens->node->content;
	return (token->quote == QUOTE_NONE);
}

// redirect->kind is NODE_KIND_HEREDOC
t_result	expand_for_heredoc(t_redirect *redirect, t_context *context)
{
	if (!is_expand_in_heredoc(redirect))
		return (SUCCESS);
	return (expand_variables_in_heredoc(redirect, context));
}
