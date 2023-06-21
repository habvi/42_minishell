#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include "ft_hash.h"

# define SUCCESS		0
# define FAILURE		1
# define PROCESS_ERROR	(-1)

# define LIST_SIZE	65536

typedef struct s_env t_env;

struct s_env
{
	t_hash	*hash;

	int		(*set) (t_env *env, char *key, char *value);	// export
	int		(*append) (t_env *env, char *key, char *value);	// export
	char	*(*get) (t_env *env, char *key);				// expansion
	int		(*unset) (t_env *env, char *key);				// unset

	void	(*list) (t_env *env);	// env
	void	(*list_all) (t_env *env);	// export
	void	(*del_value) (void *);
};

#endif //ENV_H
