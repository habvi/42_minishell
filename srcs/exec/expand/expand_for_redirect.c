#include "minishell.h"
#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"

static bool	is_ambiguous_redirect(t_redirect *redirect)
{
	return (redirect->tokens->size != 1);
}

t_result	expand_for_filename_each(t_redirect *redirect, t_context *context)
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
	ft_free((void **)&original_token);
	return (result);
}

// OK [redirect_symbol]-[file]
// NG [redirect_symbol]-[redirect_symbol]: dropped $var
//    [redirect_symbol]-[file]-[file]    : splitted $var
