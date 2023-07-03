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

static bool	is_valid_token(const char *token)
{
	(void)token;
	return (true);
}

static t_result	set_correct_syntax_token_kind(t_deque *tokens, t_context *context)
{
	t_deque_node	*token_node;
	t_token			*token;

	// debug_token_dq(tokens, __func__);
	token_node = tokens->node;
	while (token_node)
	{
		token = (t_token *)token_node->content;
		if (!is_valid_token(token->str))
		{
			context->status = SYNTAX_ERROR; // todo: print syntax error
			return (FAILURE);
		}
		// set_correct_token_kind(token);
		token_node = token_node->next;
	}
	return (SUCCESS);
}

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
