#include "test.h"

void	print_token(t_token *token_head)
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
		else if (ptr->kind == nd_right_paren)
			printf(")");
		else
			printf("(EOF)");
		ptr = ptr->next;
		if (ptr)
			printf(" ");
	}
	printf("]\n");
}

void	print_token_node(t_token *token)
{
	printf("print_tree_node:[");
	if (token && token->kind == nd_num)
		printf("%d", token->val);
	else if (token && token->kind == nd_add)
		printf("+");
	else if (token && token->kind == nd_sub)
		printf("-");
	else if (token && token->kind == nd_mul)
		printf("*");
	else if (token && token->kind == nd_div)
		printf("/");
	else if (token && token->kind == nd_left_paren)
		printf("(");
	else if (token && token->kind == nd_right_paren)
		printf(")");
	else if (token)
		printf("(EOF)");
	printf("]\n");
}

void	free_token(t_token *token)
{
	t_token	*next_ptr;

	while (token)
	{
		next_ptr = token->next;
		free(token);
		token = next_ptr;
	}
}

static t_token	*new_token_node(char *term)
{
	t_token	*node;

	node = (t_token *)calloc(1, sizeof(t_token));
	node->next = NULL;
	if (!term)
		node->kind = nd_eof;
	else if (isdigit(term[0]))
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
//	new_token = new_token_node(split[i]);
//	token_add(&token_head, new_token);
	return (token_head);
}
