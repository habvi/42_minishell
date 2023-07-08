#include "minishell.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"
#include "ft_sys.h"

char	**convert_command_to_argv(t_deque *command)
{
	char			**argv;
	const size_t	size = command->size;
	size_t			i;
	t_token			*token;
	t_deque_node	*token_node;

	argv = (char **)x_malloc(sizeof(char *) * (size + 1));
	if (!argv)
		ft_abort();
	i = 0;
	token_node = command->node;
	while (token_node)
	{
		token = (t_token *)token_node->content;
		argv[i] = x_ft_strdup(token->str);
		i++;
		token_node = token_node->next;
	}
	argv[i] = NULL;
	return (argv);
}