#include <unistd.h>
#include <sys/wait.h>
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

static void	del_redirect(void *content)
{
	t_redirect	*redirect;

	if (!content)
		return ;
	redirect = (t_redirect *)content;
	deque_clear_all(&redirect->tokens, del_token);
	if (redirect->heredoc_filename)
	{
		unlink(redirect->heredoc_filename);
		ft_free(&redirect->heredoc_filename);
	}
	ft_free(&redirect);
}

static void	destroy_ast_node(t_ast *root)
{
	if (root->left)
		destroy_ast_node(root->left);
	if (root->right)
		destroy_ast_node(root->right);
	if (root->command)
		deque_clear_all(&root->command, del_token);
	if (root->redirect_list)
		deque_clear_all(&root->redirect_list, del_redirect);
	ft_free(&root);
}

static void	wait_all_child_lastly(t_ast *ast)
{
	if (!ast)
		return ;
	wait_all_child_lastly(ast->left);
	wait_all_child_lastly(ast->right);
	if (ast->pid)
		waitpid(ast->pid, NULL, NO_OPTION);
}

void	destroy_ast_tree(t_ast **root, t_result result)
{
	if (!root || !*root)
		return ;
	if (result == PROCESS_ERROR)
		wait_all_child_lastly(*root);
	destroy_ast_node(*root);
}
