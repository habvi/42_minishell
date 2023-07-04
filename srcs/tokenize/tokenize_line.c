#include "minishell.h"
#include "ms_tokenize.h"
#include "ms_builtin.h"
#include "ft_deque.h"
#include "ft_string.h"
#include "ft_sys.h"

// ((
static bool	is_concatted_paren(char token_head, char next_chr)
{
	if (ft_strchr(TOKEN_PAREN, token_head) && token_head == next_chr)
		return (true);
	return (false);
}

static bool is_token_str_word(char token_head)
{
	return (!ft_strchr(TOKEN_SYMBOL TOKEN_PAREN TOKEN_DELIM, token_head));
}

// token_str is word = !(symbol && paren)
//     &&
// next is word
static bool	is_concat_to_next(char token_head, char next_chr)
{
	if (is_token_str_word(token_head) && is_token_str_word(next_chr))
		return (true);
	if (is_concatted_paren(token_head, next_chr))
		return (true);
	return (false);
}

static t_token	*create_token_struct(char *token_str, char next_chr)
{
	t_token	*token;

	token = (t_token *)x_malloc(sizeof(t_token) * 1);
	if (!token)
		ft_abort();
	token->str = token_str;
	token->concat_next = is_concat_to_next(*token_str, next_chr);
	return (token);
}

static t_deque_node	*create_token_node(char *token_str, char next_chr)
{
	t_token			*token;
	t_deque_node	*node;

	token = create_token_struct(token_str, next_chr);
	node = deque_node_new(token);
	if (!node)
		ft_abort();
	return (node);
}

// line != NULL
t_deque	*tokenize_line(char *line)
{
	t_deque			*tokens;
	t_deque_node	*token_node;
	char			*token_str;
	char			*end;

	tokens = deque_new();
	if (!tokens)
		ft_abort();
	while (*line)
	{
		token_str = get_token_str(line, &end);
		if (!token_str)
			break ;
		token_node = create_token_node(token_str, *end);
		deque_add_back(tokens, token_node);
		line = end;
	}
	return (tokens);
}
