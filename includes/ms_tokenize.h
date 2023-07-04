#ifndef MS_TOKENIZE_H
# define MS_TOKENIZE_H

# define TOKEN_SYMBOL	"|&<>"
# define TOKEN_PAREN	"()"
# define TOKEN_QUOTE	"\"\'"
# define TOKEN_DELIM	" \t"

# include <stdbool.h>

typedef struct s_deque	t_deque;

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

/* tokenize */
t_deque	*tokenize(char *line);
t_deque	*tokenize_line(char *line);
char	*get_token_str(char *head, char **end);
char	*get_token_tail(char *head);
void	del_token(void *content);
bool	is_token_str_symbol(char *set, char chr);
bool	is_token_str_quote(char *set, char chr);

#endif //MS_TOKENIZE_H
