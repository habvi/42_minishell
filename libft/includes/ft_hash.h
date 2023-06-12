#ifndef FT_HASH_H
# define FT_HASH_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define HASH_SUCCESS	0
# define HASH_ERROR		(-1)

typedef struct s_deque_node	t_deque_node;
typedef struct s_deque		t_deque;

typedef struct s_hash_table
{
	size_t	table_size;
	size_t	key_count;
	t_deque	**table;
}	t_hash;

typedef struct s_hash_element
{
	char	*key;
	void	*content;
}	t_elem;

/* hash value */
uint64_t		gen_fnv_hash(const unsigned char *key, uint64_t hash_mod);

/* generate hash table */
// return a pointer to the hash table. On error, return NULL
t_hash			*create_hash_table(uint64_t size);

/* add key */
// add key-value pairs to table and return 0. On error, return (-1)
// if hash_value conflicts, add with the chain method
int				set_to_table(t_hash *hash, \
								char *key, \
								void *content, \
								void (*del_content)(void *));

/* find key */
t_deque_node	*find_key(t_hash *hash, const char *key);

/* get value */
void			*get_value_from_table(t_hash *hash, const char *key);

/* update value */
void			update_content_of_key(char **key, \
										void *content, \
										t_deque_node *target_node, \
										void (*del_content)(void *));

/* del key */

/* clear table */
void			clear_hash_elem(t_elem **elem, void (*del_content)(void *));
void			tmp_deque_clear_node(t_deque_node **node, \
										void (*del_content)(void *));
void			clear_hash_table(t_hash **hash, void (*del_content)(void *));

/* display hash table */
void			display_hash_table(t_hash *hash, void (*display)(void *));

#endif //FT_HASH_H
