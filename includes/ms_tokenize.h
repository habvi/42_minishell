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

# define SINGLE_QUOTE_CHR	'\''
# define DOUBLE_QUOTE_CHR	'\"'

typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;
typedef struct s_context	t_context;

typedef enum e_quote {
	QUOTE_NONE = 0,
	QUOTE_SINGLE = 1,
	QUOTE_DOUBLE = 2
}	t_quote;

typedef enum e_token_kind {
	TOKEN_KIND_WORD,
	TOKEN_KIND_OP_PIPE,
	TOKEN_KIND_OP_OR,
	TOKEN_KIND_OP_AND,
	TOKEN_KIND_REDIRECT_IN,
	TOKEN_KIND_REDIRECT_HEREDOC,
	TOKEN_KIND_REDIRECT_OUT,
	TOKEN_KIND_REDIRECT_APPEND,
	TOKEN_KIND_PAREN_LEFT,
	TOKEN_KIND_PAREN_RIGHT,
}	t_token_kind;

//todo: content of concat_next
typedef struct s_token {
	char			*str;
	t_token_kind	kind;
	t_quote			quote;
	bool			concat_next;
}	t_token;

/* tokenize */
t_deque		*tokenize(char *line, t_context *context);
t_deque		*tokenize_line(char *line);
char		*get_token_str(char *head, char **end);
char		*get_token_tail(char *head);

/* is */
bool		is_token_str_symbol(const char *str);
bool		is_token_str_quote(const char *str);
bool		is_token_str_paren(const char *str);

bool		is_concat_to_next(char token_head, char next_chr);

bool		is_token_kind_word(t_token_kind token_kind);
bool		is_token_kind_redirection(t_token_kind token_kind);

bool		is_token_kind_and_or_from_node(t_deque_node *token_node);
bool		is_token_kind_pipe_from_node(t_deque_node *token_node);
bool		is_token_kind_word_form_node(t_deque_node *token_node);
bool		is_token_kind_redirection_from_node(t_deque_node *token_node);

bool		is_token_kind_command_as_ast_node(t_deque_node *token_node);
bool		is_token_kind_paren_left_as_ast_node(t_deque_node *token_node);
bool		is_token_kind_paren_right_as_ast_node(t_deque_node *token_node);
bool		is_token_kind_subshell_as_ast_node(t_deque_node *token_node);

/* set, update */
void		set_token_kinds_all(t_deque *tokens);
void		set_token_quote_type_all(t_deque *tokens);
void		remove_quote_in_token_str(t_deque *tokens);

/* validate */
bool		is_closed_quote_all(t_deque_node *node);
bool		is_valid_paren_pair_all(t_deque_node *node);

/* init */
t_token		*init_token_struct(void);

/* destroy */
void		del_token(void *content);
void		destroy_tokens(t_deque **command, void (*del)(void *));

#endif //MS_TOKENIZE_H
