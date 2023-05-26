#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>

typedef enum e_node_kind {
	NODE_ADD = 0,
	NODE_SUB = 1,
	NODE_NUL = 2,
	NODE_DIV = 3,
	NODE_NUM = 4, // integer
}	t_node_kind;

typedef struct s_node {
	t_node_kind		kind;
	struct s_node	*left;
	struct s_node	*right;
	int				val; // use only kind == NODE_NUM
}	t_node;

#endif
