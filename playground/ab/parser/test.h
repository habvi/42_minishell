#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_deque_node	t_deque_node;
typedef struct s_deque		t_deque;

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

typedef struct s_token {
	t_deque			*head_token;
	t_deque_node	*now_token;
}	t_token;

// create_token.c
t_node	*primary(t_token *token);
t_node	*mul(t_token *token);
t_node	*expr(t_token *token);

// token_new.c
t_node	*node_new(t_node_kind kind, t_node *left, t_node *right);
t_node	*node_num_new(int val);

// tokenize.c
void	tokenize(char *str, t_deque **head_token);

#endif
