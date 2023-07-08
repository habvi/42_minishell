#ifndef MS_PARSE_H
# define MS_PARSE_H

# include <stdbool.h>
# include <unistd.h>
# include "ms_result.h"

# define HEREDOC_FILE_PREFIX	".pien_"
# define OPEN_PERMISSION		"0664"

typedef struct s_context	t_context;
typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;
typedef struct s_token		t_token;
typedef struct s_ast		t_ast;

typedef enum e_node_kind
{
	NODE_KIND_NONE,
	NODE_KIND_COMMAND,
	NODE_KIND_OP_PIPE,
	NODE_KIND_OP_OR,
	NODE_KIND_OP_AND,
	NODE_KIND_SUBSHELL,
}	t_node_kind;

typedef struct s_redirect
{
	t_deque	*list;
	int		in_fd;
	int		out_fd;
	char	*heredoc_filename;
}	t_redirect;

struct s_ast
{
	t_node_kind	kind;
	t_deque		*command; // [token1]-[token2]-...
	t_redirect	*redirects;
	int			pipe_fd[2];
	int			prev_fd;
//	bool		is_exec_in_pipe;
	pid_t		pid;
	t_ast		*left;
	t_ast		*right;
	t_ast		*parent;
};

t_ast		*parse(t_deque **tokens, t_context *context);

/* syntax check */
bool		is_parenthesis_concatenated_all(t_deque_node *node);
bool		is_valid_redirect_syntax_all(t_deque_node *node);

/* ast */
t_ast		*create_operator_list_node(t_deque_node **token_node, \
										t_context *context);
t_ast		*create_command_list_node(t_deque_node **token_node, \
										t_context *context);
t_ast		*create_command_or_subshell_node(t_deque_node **token_node, \
												t_context *context);

t_ast		*new_command_leaf(void);
t_ast		*new_ast_node(t_node_kind kind, t_ast *left, t_ast *right);
t_ast		*new_subshell_node(t_ast *left);

t_node_kind	convert_kind_token_to_node(t_deque_node *token_node);
void		dup_command_from_tokens(t_deque *command, \
									t_deque_node **token_node);
void		dup_redirection_from_tokens(t_deque *command, \
										t_deque_node **token_node);

/* heredoc */
t_result	execute_heredoc(t_ast *ast_node);
void		move_redirect_from_command(t_ast *ast_node);
char		*create_heredoc_filename(void);
t_result	open_heredoc_filedes(int *in_fd, char **filename);

/* is */
bool		is_node_kind_exec_heredoc(t_node_kind node_kind);
bool		is_node_kind_and_or(t_node_kind node_kind);

/* destroy */
void		destroy_ast_tree(t_ast **root);

/* error */
void		*ast_print_error(t_deque_node *token_node);

#endif //MS_PARSE_H