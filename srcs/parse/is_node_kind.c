#include "ms_parse.h"

static bool	is_node_kind_command(t_node_kind node_kind)
{
	return (node_kind == NODE_KIND_COMMAND);
}

static bool	is_node_kind_subshell(t_node_kind node_kind)
{
	return (node_kind == NODE_KIND_SUBSHELL);
}

bool	is_node_kind_exec_heredoc(t_node_kind node_kind)
{
	if (is_node_kind_command(node_kind))
		return (true);
	if (is_node_kind_subshell(node_kind))
		return (true);
	return (false);
}

bool	is_node_kind_and_or(t_node_kind node_kind)
{
	if (node_kind == NODE_KIND_OP_AND)
		return (true);
	if (node_kind == NODE_KIND_OP_OR)
		return (true);
	return (false);
}
