#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_sys.h"

static t_ast	*init_ast_node(void)
{
	t_ast	*new_node;

	new_node = (t_ast *)x_malloc(sizeof(t_ast));
	if (!new_node)
		ft_abort();
	new_node->kind = NODE_KIND_NONE;
	new_node->command = NULL;
	new_node->redirect_list = NULL;
	new_node->proc_fd[IN] = IN_FD_INIT;
	new_node->proc_fd[OUT] = OUT_FD_INIT;
	new_node->pipe_fd[READ] = IN_FD_INIT;
	new_node->pipe_fd[WRITE] = OUT_FD_INIT;
	new_node->prev_fd = IN_FD_INIT;
	new_node->pid = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	return (new_node);
}

t_ast	*new_command_leaf(void)
{
	t_ast	*new_node;

	new_node = init_ast_node();
	new_node->kind = NODE_KIND_COMMAND;
	new_node->command = deque_new();
	if (!new_node->command)
		ft_abort();
	return (new_node);
}

t_ast	*new_subshell_node(t_ast *left)
{
	t_ast	*new_node;

	new_node = init_ast_node();
	new_node->kind = NODE_KIND_SUBSHELL;
	new_node->command = deque_new();
	if (!new_node->command)
		ft_abort();
	new_node->left = left;
	return (new_node);
}

t_ast	*new_ast_node(t_node_kind kind, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	new_node = init_ast_node();
	new_node->kind = kind;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

void	set_parent_of_children_node(t_ast **self_node)
{
	if (!self_node || !*self_node)
		return ;
	if ((*self_node)->left)
		(*self_node)->left->parent = *self_node;
	if ((*self_node)->right)
		(*self_node)->right->parent = *self_node;
}
