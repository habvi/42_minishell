#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

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

static bool	is_valid_tokens_syntax(t_deque_node *node)
{
	if (!is_closed_quote_all(node))
		return (false);
	if (!is_valid_paren_all(node))
		return (false);
	return (true);
}

// tokens != NULL
t_deque	*tokenize(char **line, t_context *context, t_result *result)
{
	t_deque	*tokens;

	tokens = tokenize_line(*line);
	ft_free((void **)line);
	set_token_kinds_all(tokens);
	if (!is_valid_tokens_syntax(tokens->node))
	{
		context->status = SYNTAX_ERROR;
		*result = FAILURE;
		destroy_tokens(&tokens, del_token);
		return (NULL);
	}
	set_token_quote_type_all(tokens);
	remove_quote_in_token_str(tokens);
	set_is_quoted_arr(tokens);
	// debug_token_dq(tokens, "tokenize");
	return (tokens);
}
