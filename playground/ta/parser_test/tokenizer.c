#include "test.h"

void	free_token(t_token **token)
{
	t_token	*next_ptr;

	if (!token || !*token)
		return ;
	while (*token)
	{
		next_ptr = (*token)->next;
		free(*token);
		*token = next_ptr;
	}
	*token = NULL;
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
