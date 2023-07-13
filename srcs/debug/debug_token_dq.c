#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"

// tokenize:[echo], [a], [|], [echo], [b], [&&], [echo], [c]

// typedef struct s_token {
//	char		*str;
//	t_token_kind		kind;
//	t_quote		quote;
//	bool		concat_next;
//}	t_token;
//

char	*get_token_kind_str(t_token_kind kind)
{
	if (kind == TOKEN_KIND_WORD)
		return ("w");
	if (kind == TOKEN_KIND_OP_PIPE)
		return ("|");
	if (kind == TOKEN_KIND_OP_OR)
		return ("||");
	if (kind == TOKEN_KIND_OP_AND)
		return ("&&");
	if (kind == TOKEN_KIND_REDIRECT_IN)
		return ("<");
	if (kind == TOKEN_KIND_REDIRECT_HEREDOC)
		return ("<<");
	if (kind == TOKEN_KIND_REDIRECT_OUT)
		return (">");
	if (kind == TOKEN_KIND_REDIRECT_APPEND)
		return (">>");
	if (kind == TOKEN_KIND_PAREN_LEFT)
		return ("(");
	if (kind == TOKEN_KIND_PAREN_RIGHT)
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

void	debug_token_dq_node(t_deque_node *node)
{
	t_token	*token;

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

void	debug_token_dq(t_deque *deque, const char *str)
{
	ft_dprintf(STDERR_FILENO, "deque_print(%d) %s :\n", deque->size, str);
	if (deque_is_empty(deque))
		return ;
	debug_token_dq_node(deque->node);
}
