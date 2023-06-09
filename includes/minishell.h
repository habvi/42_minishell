#ifndef MINISHELL_H
# define MINISHELL_H

# define EXECVE_ERROR	(-1)
# define FORK_ERROR		(-1)
# define WAIT_ERROR		(-1)
# define PIPE_ERROR		(-1)
# define PROCESS_ERROR	(-1)
# define FATAL_ERROR	(-1)
# define UNREACHABLE	FATAL_ERROR

# define PROMPT_NAME    "minishell "

// add: hash
typedef struct params
{
	char	**env;
	bool	is_interactive;
	char	*pwd;
	int		status;
}	t_params;

// temporarily here ...
/* debug */
void	debug_func(const char *func_name, const int line_num);
void	debug_2d_array(char **array);

/* input */
char	*input_line(void);

#endif //MINISHELL_H
