#include "minishell.h"
#include "ms_tokenize.h"
#include "ms_builtin.h"
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

t_result	add_token_kind(t_deque **tokens)
{
	if (!tokens)
		return (FAILURE);
	return (SUCCESS);
}

t_deque	*tokenize(char *line)
{
	t_deque	*tokens;

	tokens = tokenize_line(line);
	if (add_token_kind(&tokens) == FAILURE)
		return (NULL);
	debug_token_dq(tokens, "tokenize");
	return (tokens);
}
