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

static void	print_ast_recursive(t_ast_node *ast)
{
	if (ast->kind == NODE_NUM)
	{
		printf("%d ", ast->val);
		return ;
	}
	print_ast_recursive(ast->left);
	print_ast_recursive(ast->right);
	print_kind(ast->kind);
}

void	print_ast(t_ast_node *ast)
{
	printf("[");
	print_ast_recursive(ast);
	printf("]\n");
}

void	free_ast_node(t_ast_node *ast)
{
	if (ast == NULL)
		return ;
	free_ast_node(ast->left);
	free_ast_node(ast->right);
	free(ast);
}
