#include "ms_tokenize.h"
#include "ft_deque.h"

static t_quote	get_token_quote_type(const char token_head_chr)
{
	if (token_head_chr == SINGLE_QUOTE_CHR)
		return (QUOTE_SINGLE);
	if (token_head_chr == DOUBLE_QUOTE_CHR)
		return (QUOTE_DOUBLE);
	return (QUOTE_NONE);
}

static void	set_each_token_quote_type(t_token *token)
{
	token->quote = get_token_quote_type(*token->str);
}

void	set_token_quote_type_all(const t_deque *tokens)
{
	t_deque_node	*token_node;
	t_token			*token;

	token_node = tokens->node;
	while (token_node)
	{
		token = (t_token *)token_node->content;
		set_each_token_quote_type(token);
		token_node = token_node->next;
	}
}
