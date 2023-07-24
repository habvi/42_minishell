#include "minishell.h"
#include "ms_parse.h"
#include "ft_deque.h"

static void	move_all_redirect_token_from_command(t_ast *ast_node)
{
	t_deque			*command;
	t_deque			*redirect_list;
	t_deque_node	*token_node;

	if (!ast_node || !ast_node->command)
		return ;
	command = ast_node->command;
	redirect_list = ast_node->redirect_list;
	token_node = command->node;
	while (token_node)
	{
		if (!is_token_kind_redirection_from_node(token_node))
		{
			token_node = token_node->next;
			continue ;
		}
		transfer_redirect_from_command(command, redirect_list, &token_node);
	}
}

void	move_redirect_from_command(t_ast *ast_node)
{
	ast_node->redirect_list = deque_new();
	if (!ast_node->redirect_list)
		ft_abort();
	move_all_redirect_token_from_command(ast_node);
}
