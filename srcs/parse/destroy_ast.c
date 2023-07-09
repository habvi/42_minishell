#include <unistd.h>
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

static void	destroy_redirects(t_redirect **redirects)
{
	if (!redirects || !*redirects)
		return ;
	deque_clear_all(&(*redirects)->list, del_token);
	if ((*redirects)->heredoc_filename)
	{
		unlink((*redirects)->heredoc_filename);
		ft_free(&(*redirects)->heredoc_filename);
	}
	ft_free(redirects);
}

static void	destroy_ast_node(t_ast *root)
{
	if (root->left)
		destroy_ast_node(root->left);
	if (root->right)
		destroy_ast_node(root->right);
	if (root->command)
		deque_clear_all(&root->command, del_token);
	if (root->redirects)
		destroy_redirects(&root->redirects);
	ft_free(&root);
}

void	*destroy_ast_tree(t_ast **root)
{
	if (!root || !*root)
		return (NULL);
	destroy_ast_node(*root);
	return (NULL);
}
