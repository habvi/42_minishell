#include "minishell.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

char	*substr_before_dollar(char **str)
{
	char	*head;
	char	*tail;
	char	*substr;

	head = *str;
	tail = *str;
	while (*tail && *tail != CHAR_DOLLAR)
		tail++;
	substr = x_ft_strndup(head, tail - head);
	*str = tail;
	return (substr);
}
