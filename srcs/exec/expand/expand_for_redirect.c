#include "minishell.h"
#include "ms_builtin.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"

static bool	is_ambiguous_redirect(t_redirect *redirect)
{
	if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
		return (false);
	return (redirect->tokens->size != 1);
}

static t_result	expand_for_redirect_file(t_redirect *redirect, \
										t_context *context)
{
	char		*original_token;
	t_result	result;

	original_token = x_ft_strdup(get_head_token_str(redirect->tokens));
	expand_processing(&redirect->tokens, context);
	split_expand_word(&redirect->tokens);
	result = is_ambiguous_redirect(redirect);
	if (result == FAILURE)
	{
		context->status = STATUS_REDIRECT_FAILURE;
		puterr_cmd_msg(original_token, ERROR_MSG_AMBIGUOUS);
	}
	ft_free(&original_token);
	return (result);
}

t_result	expand_for_redirect(t_redirect *redirect, \
									t_context *context)
{
	if (redirect->kind == TOKEN_KIND_REDIRECT_HEREDOC)
	{
		if (expand_for_heredoc(redirect, context) == PROCESS_ERROR)
			return (PROCESS_ERROR);
	}
	else
	{
		if (expand_for_redirect_file(redirect, context) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
