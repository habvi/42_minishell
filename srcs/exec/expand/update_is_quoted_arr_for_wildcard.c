#include "ms_exec.h"
#include "ms_expansion.h"
#include "ms_tokenize.h"
#include "ms_parse.h"
#include "ms_var.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"

static void	update_is_quoted_arr_by_key_op(t_token *token, \
											const char *key, \
											t_env_op op)
{
	size_t	i;

	i = 0;
	while (key[i])
		i++;
	if (op == ENV_ADD)
		i += 1;
	else
		i += 2;
	while (token->str[i])
	{
		token->is_quoted_arr[i] = IS_QUOTED;
		i++;
	}
}

static bool	is_valid_key_by_result(t_result result)
{
	return (result == SUCCESS);
}

// key=value
// 000011111
static void	update_is_quoted_arr_each(t_token *token)
{
	t_result	result;
	char		*key;
	char		*value;
	t_env_op	op;

	result = var_separate_key_value_op(token->str, &key, &value, &op);
	if (is_valid_key_by_result(result))
		update_is_quoted_arr_by_key_op(token, key, op);
	ft_free(&key);
	ft_free(&value);
}

static bool	is_command_assign(t_deque *tokens)
{
	const char	*cmd = get_head_token_str(tokens);

	if (ft_streq(cmd, CMD_EXPORT))
		return (true);
	if (ft_streq(cmd, CMD_DECLARE))
		return (true);
	return (false);
}

void	update_is_quoted_arr_for_wildcard(t_deque *tokens)
{
	t_token			*token;
	t_deque_node	*node;

	if (!tokens || !is_command_assign(tokens))
		return ;
	node = tokens->node;
	while (node)
	{
		token = (t_token *)node->content;
		if (!ft_strchr(token->str, ASSIGN_SYMBOL))
		{
			node = node->next;
			continue ;
		}
		update_is_quoted_arr_each((t_token *)node->content);
		node = node->next;
	}
}