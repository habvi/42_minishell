#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_sys.h"

static t_redirect	*init_redirect(void)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)x_malloc(sizeof(t_redirect) * 1);
	if (!redirect)
		ft_abort();
	redirect->list = deque_new();
	if (!redirect->list)
		ft_abort();
	redirect->in_fd = STDIN_FILENO;
	redirect->out_fd = STDOUT_FILENO;
	return (redirect);
}

static void	transfer_redirect_node_from_command(t_deque *from, \
												t_deque *to, \
												t_deque_node **token_node)
{
	t_deque_node	*target;
	t_deque_node	*next_node;

	target = *token_node;
	next_node = target->next;
	deque_pop_selected_node(from, target);
	deque_add_back(to, target);
	*token_node = next_node;
}

static void	move_all_redirect_token_from_command(t_ast *ast_node)
{
	t_deque			*command;
	t_deque			*list;
	t_deque_node	*token_node;

	if (!ast_node || !ast_node->command)
		return ;
	command = ast_node->command;
	token_node = command->node;
	list = ast_node->redirects->list;
	while (token_node)
	{
		if (!is_token_kind_redirection_from_node(token_node))
		{
			token_node = token_node->next;
			continue ;
		}
		transfer_redirect_node_from_command(command, list, &token_node);
		transfer_redirect_node_from_command(command, list, &token_node);
	}
}

void	move_redirect_from_command(t_ast *ast_node)
{
	ast_node->redirects = init_redirect();
	move_all_redirect_token_from_command(ast_node);
}
