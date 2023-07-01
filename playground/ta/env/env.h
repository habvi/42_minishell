#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include "ft_hash.h"

# define SUCCESS		0
# define FAILURE		1
# define PROCESS_ERROR	(-1)

# define LIST_SIZE	65536

typedef struct s_var t_var;

struct s_var
{
	t_hash	*hash;

	int		(*set) (t_var *env, char *key, char *value);	// export
	int		(*append) (t_var *env, char *key, char *value);	// export
	char	*(*get) (t_var *env, char *key);				// expansion
	int		(*unset) (t_var *env, char *key);				// unset

	void	(*list) (t_var *env);	// env
	void	(*list_all) (t_var *env);	// export
	void	(*del_value) (void *);
};

#endif //ENV_H
