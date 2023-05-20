#include "test.h"

// BNF
//  expr    = mul ("+" mul | "-" mul)*
//  mul     = primary ("*" primary | "/" primary)*
//  primary = num | "(" expr ")"

// [ref] https://www.sigbus.info/compilerbook

t_node	*new_node(t_node_kind kind, t_node *lhs, t_node *rhs)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;
	return (node);
}

t_node	*new_node_num(int val)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	node->kind = nd_num;
	node->val = val;
	return (node);
}

//t_node	*expr()
//{
//
//}

static void	print_split(char **split)
{
	size_t	i;

	i = 0;
	printf("split:[");
	while (split && split[i])
	{
		printf("%s", split[i]);
		i++;
		if (split[i])
			printf(", ");
	}
	printf("]\n");
}

static t_token	*new_token_node(char *term)
{
	t_token	*node;

	node = (t_token *)calloc(1, sizeof(t_token));
	node->next = NULL;
	if (isdigit(term[0]))
	{
		node->val = (int)strtol(term, NULL, 10);
		node->kind = nd_num;
	}
	else if (term[0] == '+')
		node->kind = nd_add;
	else if (term[0] == '-')
		node->kind = nd_sub;
	else if (term[0] == '*')
		node->kind = nd_mul;
	else if (term[0] == '/')
		node->kind = nd_div;
	else if (term[0] == '(')
		node->kind = nd_left_paren;
	else if (term[0] == ')')
		node->kind = nd_right_paren;
	return (node);
}

static void	token_add(t_token **head, t_token *new)
{
	t_token	*node;

	if (!head)
		return ;
	if (!*head)
		*head = new;
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

t_token	*tokenize(char **split)
{
	size_t	i;
	t_token	*token_head = NULL;
	t_token	*new_token;

	i = 0;
	while (split && split[i])
	{
		new_token = new_token_node(split[i]);
		token_add(&token_head, new_token);
		i++;
	}
	return (token_head);
}

static void	print_token(t_token *token_head)
{
	t_token	*ptr;

	printf("print_token:[");
	ptr = token_head;
	while (ptr)
	{
		if (ptr->kind == nd_num)
			printf("%d", ptr->val);
		else if (ptr->kind == nd_add)
			printf("+");
		else if (ptr->kind == nd_sub)
			printf("-");
		else if (ptr->kind == nd_mul)
			printf("*");
		else if (ptr->kind == nd_div)
			printf("/");
		else if (ptr->kind == nd_left_paren)
			printf("(");
		else
			printf(")");
		ptr = ptr->next;
		if (ptr)
			printf(" ");
	}
	printf("]\n");
}

int	main(int argc, char **argv)
{
	char	**split;
	t_token	*token;

	if (argc != 2)
	{
		printf("usage               : $ ./a.out \"numerical formula\"\n"
			   "available operators : +, -, *, /, (, )\n");
		return (1);
	}
	split = ft_split(argv[1], ' ');
	print_split(split);
	token = tokenize(split);
	print_token(token);
	free_2d_array(&split);
	return (0);
}
