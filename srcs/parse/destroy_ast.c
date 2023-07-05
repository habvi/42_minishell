#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

static void	destroy_ast_node(t_ast *root)
{
	if (root->left)
		destroy_ast_node(root->left);
	if (root->right)
		destroy_ast_node(root->right);
	if (root->command)
		deque_clear_all(&root->command, del_token);
	ft_free(&root);
}

void	destroy_ast_tree(t_ast **root)
{
	if (!root || !*root)
		return ;
	destroy_ast_node(*root);
}
