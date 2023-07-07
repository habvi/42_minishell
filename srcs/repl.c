#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"
#include "ft_mem.h"

t_result	read_eval_print_loop(t_context *context)
{
	t_deque		*command;
	t_result	result;
	char		*line;
	t_deque		*tokens;
	t_ast		*ast;

	result = SUCCESS;
	while (true)
	{
		line = input_line();
		if (!line)
			break ;
		tokens = tokenize(line, context);
		if (context->status != EXIT_SUCCESS)
			continue ;
		ast = parse(&tokens, context);
		if (context->status != EXIT_SUCCESS)
			continue ;
		result = execute_command(ast, context);
		destroy_ast_tree(&ast);
		if (result == PROCESS_ERROR)
			break ;
	}
	return (result);
}
