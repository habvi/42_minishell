#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"

static bool	is_expand_in_heredoc(t_redirect *redirect)
{
	t_token	*token;

	token = (t_token *)redirect->tokens->node->content;
	return (token->quote == QUOTE_NONE);
}

// redirect->kind is NODE_KIND_HEREDOC
static t_result	expand_for_heredoc_each(t_redirect *redirect, \
										t_context *context)
{
	if (!is_expand_in_heredoc(redirect))
		return (SUCCESS);
	return (expand_variables_in_heredoc(redirect, context));
}

t_result	expand_for_heredoc(t_ast *self_node, t_context *context)
{
	t_deque_node	*node;
	t_redirect		*redirect;

	if (!self_node->redirect_list)
		return (SUCCESS);
	node = self_node->redirect_list->node;
	while (node)
	{
		redirect = (t_redirect *)node->content;
		if (redirect->kind != TOKEN_KIND_REDIRECT_HEREDOC)
		{
			node = node->next;
			continue ;
		}
		if (expand_for_heredoc_each(redirect, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
		node = node->next;
	}
	return (SUCCESS);
}
