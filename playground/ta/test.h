#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <libc.h>

typedef enum	e_node_kind	t_node_kind;
typedef struct	s_node		t_node;

enum e_node_kind
{
	nd_add,
	nd_sub,
	nd_mul,
	nd_div,
	nd_num,
};

struct s_node
{
	t_node_kind	kind;
	t_node		*lhs;
	t_node		*rhs;
	int			val;
};

#endif //TEST_H
