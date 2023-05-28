#include "test.h"

static void	print_kind(t_node_kind kind)
{
	if (kind == NODE_ADD)
		printf("+ ");
	else if (kind == NODE_SUB)
		printf("- ");
	else if (kind == NODE_MUL)
		printf("* ");
	else if (kind == NODE_DIV)
		printf("/ ");
	else
		printf("\n");
}

void	print_ast(t_ast_node *ast)
{
	if (ast == NULL)
		return ;
	if (ast->kind == NODE_NUM)
	{
		printf("%d ", ast->val);
		return ;
	}
	print_ast(ast->left);
	print_ast(ast->right);
	print_kind(ast->kind);
}
