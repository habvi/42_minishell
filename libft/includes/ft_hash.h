#ifndef FT_HASH_H
# define FT_HASH_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define HASH_SUCCESS			0
# define HASH_ERROR				(-1)
# define LOAD_FACTOR_LIMIT_PCT	80

typedef struct s_deque_node	t_deque_node;
typedef struct s_deque		t_deque;

typedef struct s_hash_table
{
	size_t	table_size;
	size_t	key_count;
	t_deque	**table;
	void	(*del_value)(void *);
}	t_hash;

typedef struct s_hash_element
{
	char	*key;
	void	*value;
}	t_elem;

/* hash value */
uint64_t		hs_gen_fnv(const unsigned char *key, uint64_t hash_mod);

/* generate hash table */
// return a pointer to the hash table. On error, return NULL
t_hash			*hs_create_table(uint64_t size, void (*del_value)(void *));

/* add key */
// add key-value pairs to table and return 0. On error, return (-1)
// if hash_value conflicts, add with the chain method
int				hs_set_key(t_hash *hash, char *key, void *value);

/* find key */
t_deque_node	*hs_find_key(t_hash *hash, const char *key);

/* get value */
void			*hs_get_value(t_hash *hash, const char *key);

/* update value */
void			hs_update_value(char **key, \
								void *value, \
								t_deque_node *target_node, \
								void (*del_value)(void *));

/* del key */
void			hs_delete_key(t_hash *hash, const char *key);

/* clear table */
void			hs_clear_elem(t_elem **elem, void (*del_value)(void *));
void			hs_clear_deque_node(t_deque_node **node, \
										void (*del_value)(void *));
void			hs_clear_table(t_hash **hash);

/* display hash table */
void			hs_display(t_hash *hash, void (*display)(void *));

/* rehash */
bool			is_need_rehash(t_hash *hash);
int				hs_rehash_table(t_hash *hash);

#endif //FT_HASH_H
