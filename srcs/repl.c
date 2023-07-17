#include <stdlib.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

t_result	read_eval_print_loop(t_context *context)
{
	t_result	result;
	char		*line;
	t_deque		*tokens;
	t_ast		*ast;

	while (true)
	{
		context->is_return = false;
		result = SUCCESS;
		line = input_line();
		if (!line)
			break ;
		tokens = tokenize(line, context, &result);
		if (result == FAILURE)
			continue ;
		ast = parse(&tokens, context, &result);
		if (result == FAILURE)
			continue ;
		result = execute_command(&ast, context, result);
//		debug_print_ast_tree(ast, "repl");
		if (result == PROCESS_ERROR)
			break ;
	}
	return (result);
}
