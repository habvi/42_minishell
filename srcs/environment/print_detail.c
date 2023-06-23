#include "minishell.h"
#include "ft_deque.h"
#include "ft_dprintf.h"
#include "ft_hash.h"
#include "ft_sys.h"

// print key-value-pairs to stdout
//   include only key
//   `declare -x key="value\n`
int	env_print_detail(t_env *env)
{
	t_elem	**elems;

	elems = (t_elem **)x_malloc(sizeof(t_elem *) * env->hash->key_count);
	if (!elems)
		return (PROCESS_ERROR);
	// set key all
	// sort
	// print
	return (SUCCESS);
}
