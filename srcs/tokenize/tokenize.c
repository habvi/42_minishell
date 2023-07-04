#include <stdlib.h>
#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_string.h"

// a   b    c  |   d   eeee|f||    >   e
// [a],[b],[c],[|],[d],[e],[&&],[f],[>],[e]

// aaaa"b"  'c'&& d|e>>f
// [aaaa]=["b"], ['c'], [&&], [d], [|], [e], [>>], [f]

// a| > |c&&& d|e>>>f
// [a],[|],[>], [|], [c], [&&&], [d], [|], [e], [>>>], [f]
//     ^^^  ^    ^         ^^^                   ^^^
//                          error            error

// ',"", $
// a  $b $? "a'b'c$d"e'f'
// [a], [$b], [$?], ["a'b'c$d"]=[e]=['f']

// Unclosed -> error
//  a  "b       b\0
//  [a] ["b  ||   b] error, None

static bool	is_valid_paren_each_token(const char *token)
{
	(void)token;
	return (true);
}

static bool	is_valid_paren_all(t_deque_node *node, t_context *context)
{
	t_token	*token;

	while (node)
	{
		token = (t_token *)node->content;
		if (!is_valid_paren_each_token(token->str))
		{
			context->status = SYNTAX_ERROR; // todo: print syntax error
			ft_dprintf(STDERR_FILENO, "%s\n", ERROR_MSG_SYNTAX); // tmp
			return (false);
		}
		node = node->next;
	}
	return (true);
}

// )(
static bool	is_valid_tokens_syntax(t_deque_node *node, t_context *context)
{
	if (!is_closed_quote_all(node, context))
		return (false);
	if (!is_valid_paren_all(node, context))
		return (false);
	return (true);
}

// tokens != NULL
t_deque	*tokenize(char *line, t_context *context)
{
	t_deque	*tokens;

	tokens = tokenize_line(line);
	set_token_kinds_all(tokens);
	if (!is_valid_tokens_syntax(tokens->node, context))
	{
//		destroy_tokens(tokens, del_token);
//		return (NULL);
	}
	set_token_quote_type_all(tokens);

	debug_token_dq(tokens, "tokenize");
	context->status = EXIT_SUCCESS;
	return (tokens);
}
