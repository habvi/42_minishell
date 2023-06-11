#ifndef FT_HASH_H
# define FT_HASH_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define HASH_SUCCESS	0
# define HASH_ERROR		(-1)

typedef struct s_deque	t_deque;

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
uint64_t	generate_fnv_hash_64(const unsigned char *key, uint64_t hash_mod);

/* generate hash table */
// return a pointer to the hash table. On error, return NULL
t_hash		*create_hash_table(uint64_t size);

/* add key */
// add key-value pairs to table and return 0. On error, return (-1)
// if hash_value conflicts, add with the chain method
int			set_to_table(t_hash *hash, char *key, void *content);

/* find key */
t_deque_node	*find_key(t_hash *hash, const char *key);

/* get value */

/* update value */
void		update_content_of_key(t_hash *hash, char *key, void *content);

/* del key */

/* clear table */
//void		clear_hash_elem(t_elem **elem, void (*del)(void *))
void		clear_hash_table(t_hash **hash);

/* display hash table */
void		display_hash_table(t_hash *hash, void (*display)(void *));

#endif //FT_HASH_H
