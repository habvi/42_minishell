#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

// tokenize:[echo], [a], [|], [echo], [b], [&&], [echo], [c]

// typedef struct s_token {
//	char		*str;
//	t_kind		kind;
//	t_quote		quote;
//	bool		concat_next;
//}	t_token;
//

static char	*get_token_kind_str(t_kind kind)
{
	if (kind == KIND_WORD)
		return ("w");
	if (kind == KIND_OP_PIPE)
		return ("|");
	if (kind == KIND_OP_OR)
		return ("||");
	if (kind == KIND_OP_AND)
		return ("&&");
	if (kind == KIND_REDIRECT_IN)
		return ("<");
	if (kind == KIND_REDIRECT_HEREDOC)
		return ("<<");
	if (kind == KIND_REDIRECT_OUT)
		return (">");
	if (kind == KIND_REDIRECT_APPEND)
		return (">>");
	if (kind == KIND_PAREN_LEFT)
		return ("(");
	if (kind == KIND_PAREN_RIGHT)
		return (")");
	return ("Error");
}

static char	*get_quote_str(t_quote quote)
{
	if (quote == QUOTE_SINGLE)
		return ("\'");
	if (quote == QUOTE_DOUBLE)
		return ("\"");
	if (quote == QUOTE_NONE)
		return ("");
	return ("Error");
}

static char	*get_concat_str(bool is_concat_next)
{
	if (is_concat_next)
		return ("=");
	return ("");
}

void	debug_token_dq(t_deque *deque, const char *str)
{
	t_deque_node	*node;
	t_token			*token;

	ft_dprintf(STDERR_FILENO, "deque_print(%d) %s :\n", deque->size, str);
	if (deque_is_empty(deque))
		return ;
	node = deque->node;
	while (node)
	{
		token = (t_token *)node->content;
		ft_dprintf(2, "  str   :[%s]\n", token->str);
		ft_dprintf(2, "  kind  :[%s]\n", get_token_kind_str(token->kind));
		ft_dprintf(2, "  quote :[%s]\n", get_quote_str(token->quote));
		ft_dprintf(2, "  concat:[%s]\n", get_concat_str(token->concat_next));
		node = node->next;
		if (node)
			ft_dprintf(STDERR_FILENO, "\n");
	}
	ft_dprintf(STDERR_FILENO, "\n");
}
