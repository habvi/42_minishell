#ifndef TEST_H
# define TEST_H

# include <ctype.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
//# include <libc.h>
# include <stdlib.h>

# include "../../../libft/includes/libft.h"

# define MSG_USAGE		"usage               : $ ./a.out \"numerical formula\"\navailable operators : +, -, *, /, (, )\n"
# define MAX_DEPTH		100
# define PRINT_WIDTH	3

typedef enum	e_node_kind	t_node_kind;
typedef struct	s_tree		t_tree;
typedef struct	s_token		t_token;

enum e_node_kind
{
	// num
	nd_num,

	// priority
	nd_priority,

	// operator
	nd_add,
	nd_sub,
	nd_mul,
	nd_div,

	// unnecessary...?
	nd_left_paren,
	nd_right_paren,
	nd_eof,
};

struct s_token
{
	t_node_kind	kind;
	int			val;
	char		operator;
	t_token		*next;
};

struct s_tree
{
	t_node_kind	kind;
	int			val;
	t_tree		*lhs;
	t_tree		*rhs;
};


// tokenizer
void	free_token(t_token **token);
t_token	*tokenize(char **split);


// parser
t_tree	*expression(t_token **token);
t_tree	*term(t_token **token);
t_tree	*primary(t_token **token);


// calculator
int     calculator(t_tree *node);


// tree
t_tree	*new_node(t_node_kind kind, t_tree *lhs, t_tree *rhs);
t_tree	*new_num_leaf(int val);
t_tree	*new_priority_node(t_tree *next);
void	free_tree(t_tree **node);
char	get_operator_char(t_tree *node);
size_t	get_depth(t_tree *node);


// print
void	print_split(char **split);
void	print_token(t_token *token_head);
void	print_token_node(t_token *token);
void	print_tree(t_tree *tree);


#endif //TEST_H
