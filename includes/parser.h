#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_deque					t_deque;
typedef struct s_deque_node				t_deque_node;

typedef struct s_token					t_token;

typedef enum e_quote					t_quote;
typedef enum e_concat					t_concat;

//-----------------

typedef enum e_node_type				t_type;
typedef struct s_abstract_syntax_tree	t_ast; //too long?

enum e_node_type {
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
};

struct s_abstract_syntax_tree {
	t_type	type;
	t_deque	*cmd_head;
	t_ast	*left;
	t_ast	*right;
};

/* parser */
t_ast	*parser(t_deque *dq_head);
bool	is_equal_strings(const char *str1, const char *str2);
bool	is_pipe_token(t_deque *dq_token);

/* syntax tree */
t_ast	*new_command_leaf(t_deque *cmd_head);
t_ast	*new_node(t_type type, t_ast *left, t_ast *right);
void	ast_clear(t_ast **root);
void	print_ast(t_ast *root);

#endif //PARSER_H
