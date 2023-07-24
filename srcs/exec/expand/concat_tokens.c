#include "minishell.h"
#include "ms_parse.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_sys.h"

static char	*concat_token_str(const t_token *token1, const t_token *token2)
{
	char	*concat_str;

	concat_str = x_ft_strjoin(token1->str, token2->str);
	return (concat_str);
}

static bool	*concat_is_quoted_arr(const t_token *token1, const t_token *token2)
{
	const size_t	len1 = ft_strlen(token1->str);
	const size_t	len2 = ft_strlen(token2->str);
	bool			*is_quoted_arr;
	size_t			i;
	size_t			j;

	is_quoted_arr = (bool *)x_malloc(sizeof(bool) * (len1 + len2));
	if (!is_quoted_arr)
		ft_abort();
	i = 0;
	while (token1->str && token1->str[i])
	{
		is_quoted_arr[i] = token1->is_quoted_arr[i];
		i++;
	}
	j = 0;
	while (token2->str && token2->str[j])
	{
		is_quoted_arr[i + j] = token2->is_quoted_arr[j];
		j++;
	}
	return (is_quoted_arr);
}

static void	swap_next_token_str_and_is_quoted_arr(t_deque_node *next, \
													char *concat_str, \
													bool **is_quoted_arr)
{
	t_token	*next_token;

	next_token = (t_token *)next->content;
	ft_free((void **)&next_token->str);
	next_token->str = concat_str;
	ft_free((void **)&next_token->is_quoted_arr);
	next_token->is_quoted_arr = *is_quoted_arr;
}

// tokens=[token1]=[token2]-[token3]=[token4]
//         ^now   ^ concat_next
// *node != NULL
static void	concat_tokens_each(t_deque *tokens, t_deque_node **node)
{
	t_deque_node	*next;
	char			*concat_str;
	bool			*concat_is_quoted;

	next = (*node)->next;
	concat_str = concat_token_str((*node)->content, next->content);
	concat_is_quoted = concat_is_quoted_arr((*node)->content, next->content);
	swap_next_token_str_and_is_quoted_arr(next, concat_str, &concat_is_quoted);
	deque_pop_selected_node(tokens, *node);
	deque_clear_node(node, del_token);
	*node = next;
}

// tokens=[token1]=[token2]-[token3]=[token4]
//    ->  [token1token2]-[token3token4]
// if concat_next=true; next token exist
void	concat_tokens(t_deque *tokens)
{
	t_token			*token;
	t_deque_node	*node;

	if (!tokens)
		return ;
	node = tokens->node;
	while (node)
	{
		token = (t_token *)node->content;
		if (!token->concat_next)
		{
			node = node->next;
			continue ;
		}
		concat_tokens_each(tokens, &node);
	}
}
