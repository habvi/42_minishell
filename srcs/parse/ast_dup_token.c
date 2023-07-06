#include "minishell.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

static t_token	*dup_token(t_token *token)
{
	t_token	*new_token;

	new_token = init_token_struct();
	new_token->str = x_ft_strdup(token->str);
	new_token->kind = token->kind;
	new_token->quote = token->quote;
	new_token->concat_next = token->concat_next;
	return (new_token);
}

static t_deque_node	*deque_dup_node(t_token *token)
{
	t_deque_node	*new_node;
	t_token			*new_token;

	new_token = dup_token(token);
	new_node = deque_node_new((void *)new_token);
//	ft_dprintf(2, "dup_cmd:%s\n", new_token->str);
	if (!new_node)
		ft_abort();
	return (new_node);
}

static void	add_dup_token_to_command(t_deque *command, \
										t_deque_node **token_node)
{
	t_token			*token;
	t_deque_node	*dup_node;

	token = (*token_node)->content;
	dup_node = deque_dup_node(token);
	deque_add_back(command, dup_node);
	*token_node = (*token_node)->next;
}

void	dup_command_from_tokens(t_deque *command, t_deque_node **token_node)
{
	t_node_kind	node_kind;

	if (!token_node)
		return ;
	while (*token_node)
	{
		node_kind = convert_kind_token_to_node(*token_node);
		if (node_kind != NODE_KIND_COMMAND && node_kind != NODE_KIND_NONE)
			return ;
		add_dup_token_to_command(command, token_node);
	}
}

// < w >> w >w <w
void	dup_redirection_from_tokens(t_deque *command, t_deque_node **token_node)
{
	t_token	*token;

	if (!token_node)
		return ;
	while (*token_node)
	{
		token = (*token_node)->content;
		if (!is_token_kind_redirection(token->kind))
			return ;
		add_dup_token_to_command(command, token_node);
		add_dup_token_to_command(command, token_node);
	}
}
