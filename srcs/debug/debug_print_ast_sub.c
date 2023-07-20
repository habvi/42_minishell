#include "ms_parse.h"

char	*get_tree_symbol(bool is_rhs)
{
	if (is_rhs)
		return ("└");
	return ("├");
}

char	get_tree_space(bool is_rhs)
{
	if (is_rhs)
		return (' ');
	return ('|');
}

char	*get_ast_node_kind_str(t_node_kind node_kind)
{
	if (node_kind == NODE_KIND_OP_PIPE)
		return ("|");
	if (node_kind == NODE_KIND_OP_OR)
		return ("||");
	if (node_kind == NODE_KIND_OP_AND)
		return ("&&");
	if (node_kind == NODE_KIND_SUBSHELL)
		return ("(");
	return ("");
}
