#include "test.h"

static void	calc_each_node(t_ast_node *ast)
{
	if (ast->kind == NODE_ADD)
		ast->val = ast->left->val + ast->right->val;
	else if (ast->kind == NODE_SUB)
		ast->val = ast->left->val - ast->right->val;
	else if (ast->kind == NODE_MUL)
		ast->val = ast->left->val * ast->right->val;
	else if (ast->kind == NODE_DIV)
		ast->val = ast->left->val / ast->right->val;
	else
		error_exit(__func__, "wrong operation...?");
}

static void	calc_ast_recursive(t_ast_node *ast)
{
	if (ast->kind == NODE_NUM)
		return ;
	calc_ast_recursive(ast->left);
	calc_ast_recursive(ast->right);
	calc_each_node(ast);
}

int	calc_from_ast(t_ast_node *ast)
{
	calc_ast_recursive(ast);
	return (ast->val);
}
