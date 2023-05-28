#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef enum e_node_kind {
	NODE_NONE = 0,
	NODE_ADD = 1,
	NODE_SUB = 2,
	NODE_MUL = 3,
	NODE_DIV = 4,
	NODE_NUM = 5, // integer
	NODE_EOF = 6
}	t_node_kind;

typedef struct	s_token {
	char			*str;
	t_node_kind		kind;
	int				val; // use only kind == NODE_NUM
	struct s_token	*next;
}	t_token;

typedef struct s_ast_node {
	char				*str;
	t_node_kind			kind;
	int					val; // use only kind == NODE_NUM
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

// ast_node_new.c
t_ast_node	*node_new(char *str, t_node_kind kind, t_ast_node *left, t_ast_node *right);
t_ast_node	*node_num_new(char *str, int val);

// is_equal_strings.c
bool	is_equal_strings(const char *s1, const char *s2);

// tokenize.c
t_token *tokenize(char *p);

// util_token.c
void	print_token(t_token *token);
void	free_token(t_token *token);
void	error_exit(const char *func_name, const char *msg);

#endif
