#include <signal.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_signal.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

static sig_atomic_t	g_sig = INIT_SIG;

void	sigint_handler_for_prompt(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
	}
}

static int	event_by_sigint_for_prompt(void)
{
	if (g_sig == SIGINT)
	{
		rl_replace_line(EMPTY_LINE, STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
		rl_done = true;
	}
	return (0);
}

static void	init_repl_var(t_context *context, t_result *result)
{
	context->is_return = false;
	*result = SUCCESS;
	if (g_sig == SIGINT)
		context->status = STATUS_SIG_BASE + SIGINT;
	if (context->is_interactive && !context->_is_test)
	{
		rl_catch_signals = true; // false -> not display ^C // todo:init?
		rl_event_hook = event_by_sigint_for_prompt;
	}
	rl_done = false;
	g_sig = INIT_SIG;
}

t_result	read_eval_print_loop(t_context *context)
{
	t_result	result;
	char		*line;
	t_deque		*tokens;
	t_ast		*ast;

	while (true)
	{
		set_signal_for_prompt();
		init_repl_var(context, &result);
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
