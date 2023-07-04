#include "ms_tokenize.h"
#include "ft_string.h"

// ||| -> [||], [|]
//         ^^ max_len=2
static char	*get_token_symbol_tail(char *head)
{
	char		*tail;
	const char	symbol_chr = *head;

	tail = head + 1;
	if (*tail == symbol_chr)
		tail++;
	return (tail);
}

static char	*get_token_paren_tail(char *head)
{
	char	*tail;

	tail = head + 1;
	return (tail);
}

static char	*get_token_quote_tail(char *head)
{
	char		*tail;
	const char	set[2] = {*head, '\0'};

	head++;
	tail = ft_find_set_in_str(head, set);
	if (*tail)
		tail++;
	return (tail);
}

static char	*get_token_word_tail(char *head)
{
	char		*tail;
	const char	*set = TOKEN_SYMBOL TOKEN_QUOTE TOKEN_DELIM TOKEN_PAREN;

	head++;
	tail = ft_find_set_in_str(head, set);
	return (tail);
}

// token_str
// ^head    ^ tail
// 3 patterns: token str is 1)symbol, 2)quoted, 3)word
char	*get_token_tail(char *head)
{
	char	*tail;

	if (is_token_str_symbol(*head))
		tail = get_token_symbol_tail(head);
	else if (is_token_str_quote(*head))
		tail = get_token_quote_tail(head);
	else if (is_token_str_paren(*head))
		tail = get_token_paren_tail(head);
	else
		tail = get_token_word_tail(head);
	return (tail);
}
