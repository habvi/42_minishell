#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_string.h"

static bool	is_valid_token(const char *token)
{
	(void)token;
	return (true);
}

static void	set_correct_token_kind(t_token *token)
{
	const char	*token_str = token->str;

	if (ft_streq(token_str, KIND_STR_OP_PIPE))
		token->kind = KIND_OP_PIPE;
	else if (ft_streq(token_str, KIND_STR_OP_OR))
		token->kind = KIND_OP_OR;
	else if (ft_streq(token_str, KIND_STR_OP_AND))
		token->kind = KIND_OP_AND;
	else if (ft_streq(token_str, KIND_STR_REDIRECT_IN))
		token->kind = KIND_REDIRECT_IN;
	else if (ft_streq(token_str, KIND_STR_REDIRECT_HEREDOC))
		token->kind = KIND_REDIRECT_HEREDOC;
	else if (ft_streq(token_str, KIND_STR_REDIRECT_OUT))
		token->kind = KIND_REDIRECT_OUT;
	else if (ft_streq(token_str, KIND_STR_REDIRECT_APPEND))
		token->kind = KIND_REDIRECT_APPEND;
	else if (ft_streq(token_str, KIND_STR_PAREN_LEFT))
		token->kind = KIND_PAREN_LEFT;
	else if (ft_streq(token_str, KIND_STR_PAREN_RIGHT))
		token->kind = KIND_PAREN_RIGHT;
	else
		token->kind = KIND_WORD;
}

t_result	set_correct_syntax_token_kind(t_deque *tokens, t_context *context)
{
	t_deque_node	*token_node;
	t_token			*token;

	// debug_token_dq(tokens, __func__);
	token_node = tokens->node;
	while (token_node)
	{
		token = (t_token *)token_node->content;
		if (!is_valid_token(token->str))
		{
			context->status = SYNTAX_ERROR; // todo: print syntax error
			return (FAILURE);
		}
		set_correct_token_kind(token);
		token_node = token_node->next;
	}
	return (SUCCESS);
}
