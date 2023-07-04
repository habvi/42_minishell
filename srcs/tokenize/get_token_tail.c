#include "minishell.h"
#include "ms_tokenize.h"
#include "ms_builtin.h"
#include "ft_mem.h"
#include "ft_string.h"

static char	*get_token_symbol_tail(char *head, const char symbol)
{
	while (*head && *head == symbol)
		head++;
	return (head);
}

static bool	is_token_str_symbol(char *set, const char chr)
{
	return (ft_strchr(set, chr));
}

static bool	is_token_str_quote(char *set, const char chr)
{
	return (ft_strchr(set, chr));
}

// 3 patterns: token str is 1)symbol, 2)quoted, 3)word
char	*get_token_tail(char *head)
{
	char		*tail;
	const char	head_chr = *head;

	head++;
	if (is_token_str_symbol(TOKEN_SYMBOL, head_chr))
		tail = get_token_symbol_tail(head, head_chr);
	else if (is_token_str_quote(TOKEN_QUOTE, head_chr))
	{
		tail = ft_find_set_in_str(head, (const char [2]){head_chr, 0});
		if (*tail)
			tail++;
	}
	else
		tail = ft_find_set_in_str(head, TOKEN_SYMBOL TOKEN_QUOTE TOKEN_DELIM);
	return (tail);
}
