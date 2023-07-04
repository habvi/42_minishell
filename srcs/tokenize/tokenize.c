#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

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

t_deque	*tokenize(char *line, t_context *context)
{
	t_deque	*tokens;

	tokens = tokenize_line(line);
	if (!tokens)
		return (NULL); // todo: iru? set status?
	if (set_correct_syntax_token_kind(tokens, context) == FAILURE)
		return (NULL);
	// debug_token_dq(tokens, "tokenize");
	return (tokens);
}
