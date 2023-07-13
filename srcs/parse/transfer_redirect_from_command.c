#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_sys.h"

static t_redirect	*init_redirect(void)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)x_malloc(sizeof(t_redirect) * 1);
	if (!redirect)
		ft_abort();
	redirect->kind = TOKEN_KIND_WORD;
	redirect->tokens = deque_new();
	if (!redirect->tokens)
		ft_abort();
	redirect->heredoc_filename = NULL;
	return (redirect);
}

static t_token_kind	get_redirect_kind_and_clear_node(t_deque *command, \
													t_deque_node **token_node)
{
	t_deque_node	*target_node;
	t_deque_node	*next_node;
	t_token_kind	kind;

	target_node = *token_node;
	next_node = target_node->next;
	deque_pop_selected_node(command, target_node);
	kind = get_token_kind(target_node);
	deque_clear_node(&target_node, del_token);
	*token_node = next_node;
	return (kind);
}

static void	move_redirect_file_from_command(t_deque *command, \
											t_deque_node **token_node, \
											t_deque *redirect_tokens)
{
	t_deque_node	*target_node;
	t_deque_node	*next_node;

	target_node = *token_node;
	next_node = target_node->next;
	deque_pop_selected_node(command, target_node);
	deque_add_back(redirect_tokens, target_node);
	*token_node = next_node;
}

static t_redirect	*create_redirect_from_command(t_deque *command, \
													t_deque_node **token_node)
{
	t_redirect		*redirect;

	redirect = init_redirect();
	redirect->kind = get_redirect_kind_and_clear_node(command, token_node);
	move_redirect_file_from_command(command, token_node, redirect->tokens);
	return (redirect);
}

void	transfer_redirect_from_command(t_deque *command, \
										t_deque *redirect_list, \
										t_deque_node **token_node)
{
	t_redirect		*redirect;
	t_deque_node	*new_node;

	redirect = create_redirect_from_command(command, token_node);
	new_node = deque_node_new(redirect);
	if (!new_node)
		ft_abort();
	deque_add_back(redirect_list, new_node);
}
