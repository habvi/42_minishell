#ifndef MS_TOKENIZE_H
# define MS_TOKENIZE_H

# include <stdbool.h>
# include "ms_result.h"

# define TOKEN_SYMBOL	"|&<>"
# define TOKEN_PAREN	"()"
# define TOKEN_QUOTE	"\"\'"
# define TOKEN_DELIM	" \t"

# define KIND_STR_OP_PIPE			"|"
# define KIND_STR_OP_OR				"||"
# define KIND_STR_OP_AND			"&&"
# define KIND_STR_REDIRECT_IN		"<"
# define KIND_STR_REDIRECT_HEREDOC	"<<"
# define KIND_STR_REDIRECT_OUT		">"
# define KIND_STR_REDIRECT_APPEND	">>"
# define KIND_STR_PAREN_LEFT		"("
# define KIND_STR_PAREN_RIGHT		")"

# define SYNTAX_ERROR	2

typedef struct s_deque		t_deque;
typedef struct s_context	t_context;

typedef enum e_quote {
	QUOTE_NONE = 0,
	QUOTE_SINGLE = 1,
	QUOTE_DOUBLE = 2
}	t_quote;

typedef enum e_token_kind {
	KIND_WORD,
	KIND_OP_PIPE,
	KIND_OP_OR,
	KIND_OP_AND,
	KIND_REDIRECT_IN,
	KIND_REDIRECT_HEREDOC,
	KIND_REDIRECT_OUT,
	KIND_REDIRECT_APPEND,
	KIND_PAREN_LEFT,
	KIND_PAREN_RIGHT,
}	t_kind;

typedef struct s_token {
	char		*str;
	t_kind		kind;
	t_quote		quote;
	bool		concat_next;
}	t_token;

// todo: indent
/* tokenize */
t_deque	*tokenize(char *line, t_context *context);
t_deque	*tokenize_line(char *line);
char	*get_token_str(char *head, char **end);
char	*get_token_tail(char *head);
void	del_token(void *content);
bool	is_token_str_symbol(char *set, char chr);
bool	is_token_str_quote(char *set, char chr);

t_result	set_correct_syntax_token_kind(t_deque *tokens, t_context *context);

#endif //MS_TOKENIZE_H
