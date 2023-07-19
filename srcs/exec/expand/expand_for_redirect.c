#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"

static bool	is_ambiguous_redirect(t_redirect *redirect)
{
	return (redirect->tokens->size != 1);
}

static t_result	expand_for_filename_each(t_redirect *redirect, \
											t_context *context)
{
	char		*original_token;
	t_result	result;

	result = SUCCESS;
	original_token = x_ft_strdup(get_head_token_str(redirect->tokens));
	if (expand_processing(&redirect->tokens, context) == PROCESS_ERROR)
		return (PROCESS_ERROR);
	split_expand_word(&redirect->tokens);
	if (is_ambiguous_redirect(redirect))
	{
		context->status = STATUS_REDIRECT_FAILURE;
		puterr_cmd_msg(original_token, ERROR_MSG_AMBIGUOUS);
		result = FAILURE;
	}
	ft_free(&original_token);
	return (result);
}

// OK [redirect_symbol]-[file]
// NG [redirect_symbol]-[redirect_symbol]: dropped $var
//    [redirect_symbol]-[file]-[file]    : splitted $var

// redirect_list != NULL
// if redirect failure, proc_fd[IN/OUT] = (-1)
t_result	expand_for_filename(t_ast *self_node, t_context *context)
{
	t_deque_node	*node;
	t_redirect		*redirect;
	t_result		result;

	node = self_node->redirect_list->node;
	while (node)
	{
		redirect = (t_redirect *)node->content;
		if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
		{
			node = node->next;
			continue ;
		}
		result = expand_for_filename_each(redirect, context);
		if (result == FAILURE || result == PROCESS_ERROR)
			return (result);
		node = node->next;
	}
	return (SUCCESS);
}
