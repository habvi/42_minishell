#include <unistd.h>
#include <sys/wait.h>
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

static void	wait_all_child_lastly(t_ast *ast)
{
	if (!ast)
		return ;
	wait_all_child_lastly(ast->left);
	wait_all_child_lastly(ast->right);
	if (ast->pid)
		waitpid(ast->pid, NULL, NO_OPTION);
}

void	destroy_ast_node_recursive(t_ast **root)
{
	if ((*root)->left)
		destroy_ast_node_recursive(&(*root)->left);
	if ((*root)->right)
		destroy_ast_node_recursive(&(*root)->right);
	if ((*root)->command)
		deque_clear_all(&(*root)->command, del_token);
	if ((*root)->redirect_list)
		deque_clear_all(&(*root)->redirect_list, del_redirect);
	ft_free(root);
}

void	destroy_ast_tree(t_ast **root, t_result exec_result)
{
	if (!root || !*root)
		return ;
	if (exec_result == PROCESS_ERROR)
		wait_all_child_lastly(*root);
	destroy_ast_node_recursive(root);
}
