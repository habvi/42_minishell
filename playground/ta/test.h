#ifndef TEST_H
# define TEST_H

# include <ctype.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <libc.h>

# include "../../libft/includes/libft.h"

typedef enum	e_node_kind	t_node_kind;
typedef struct	s_node		t_node;
typedef struct	s_token		t_token;

enum e_node_kind
{
	nd_num,
	nd_add,
	nd_sub,
	nd_mul,
	nd_div,
	nd_left_paren,
	nd_right_paren,
};

struct s_node
{
	t_node_kind	kind;
	t_node		*lhs;
	t_node		*rhs;
	int			val;
};

struct s_token
{
	t_node_kind	kind;
	int			val;
	char		operator;
	t_token		*next;
};

#endif //TEST_H
