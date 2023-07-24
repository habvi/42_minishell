#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

static bool	get_is_quoted_value(const t_quote quote)
{
	return (quote != QUOTE_NONE);
}

void	set_is_quoted_value_to_arr(t_token *token)
{
	const size_t	len = ft_strlen(token->str);
	bool			*is_quoted_arr;
	bool			is_quoted_value;

	if (token->kind != TOKEN_KIND_WORD)
		return ;
	is_quoted_arr = (bool *)x_malloc(sizeof(bool) * len);
	if (!is_quoted_arr)
		ft_abort();
	is_quoted_value = get_is_quoted_value(token->quote);
	ft_memset(is_quoted_arr, is_quoted_value, sizeof(bool) * len);
	ft_free((void **)&token->is_quoted_arr);
	token->is_quoted_arr = is_quoted_arr;
}

void	set_is_quoted_arr(t_deque *tokens)
{
	t_deque_node	*token_node;

	token_node = tokens->node;
	while (token_node)
	{
		set_is_quoted_value_to_arr(token_node->content);
		token_node = token_node->next;
	}
}
