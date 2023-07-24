#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "minishell.h"
#include "ms_exec.h"
#include "ms_parse.h"
#include "ms_signal.h"
#include "ms_tokenize.h"
#include "ft_deque.h"

volatile sig_atomic_t	g_sig = INIT_SIG;

static int	event_by_sigint_for_prompt(void)
{
	if (g_sig == SIGINT)
	{
		rl_replace_line(EMPTY_LINE, STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
		rl_done = true;
	}
	return (EXIT_SUCCESS);
}

static void	init_rl_var(bool is_rl_event_hook_off)
{
	rl_outstream = stderr;
	rl_done = false;
	if (!is_rl_event_hook_off)
	{
		rl_catch_signals = true;
		rl_event_hook = event_by_sigint_for_prompt;
	}
}

static void	init_repl_var(t_context *context, t_result *result)
{
	context->is_return = false;
	*result = SUCCESS;
	if (g_sig == SIGINT)
		context->status = STATUS_SIG_BASE + SIGINT;
	g_sig = INIT_SIG;
}

static void	init_each_loop(t_context *context, t_result *result)
{
	init_repl_var(context, result);
	init_rl_var(context->is_rl_event_hook_off);
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
		init_each_loop(context, &result);
		line = input_line();
		if (!line)
			break ;
		tokens = tokenize(line, context, &result);
		if (result == FAILURE)
			continue ;
		ast = parse(&tokens, context, &result);
		if (result == BREAK || result == FAILURE)
			continue ;
		result = execute_command(&ast, context, result);
//		debug_print_ast_tree(ast, "repl");
		if (result == PROCESS_ERROR)
			break ;
	}
	return (result);
}
