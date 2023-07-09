#include "ms_parse.h"

char	*get_node_kind_str(t_node_kind kind)
{
	if (kind == NODE_KIND_NONE)
		return ("NONE");
	if (kind == NODE_KIND_COMMAND)
		return ("COMMAND");
	if (kind == NODE_KIND_OP_PIPE)
		return ("|");
	if (kind == NODE_KIND_OP_OR)
		return ("||");
	if (kind == NODE_KIND_OP_AND)
		return ("&&");
	if (kind == NODE_KIND_SUBSHELL)
		return ("()");
	return ("ERROR");
}
