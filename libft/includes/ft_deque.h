#ifndef FT_DEQUE_H
# define FT_DEQUE_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_deque_node {
	void				*content;
	struct s_deque_node	*next;
	struct s_deque_node	*prev;
}	t_deque_node;

typedef struct s_deque {
	t_deque_node	*node;
	size_t			size;
}	t_deque;

/* add */
void			deque_add_back(t_deque *deque, t_deque_node *new_node);
void			deque_add_first_node(t_deque *deque, t_deque_node *new_node);
void			deque_add_front(t_deque *deque, t_deque_node *new_node);

/* clear */
void			deque_clear_all(t_deque **deque, void (*del)(void *));
void			deque_clear_node(t_deque_node **node, void (*del)(void *));

/* is_empty */
bool			deque_is_empty(const t_deque *deque);

/* pop */
t_deque_node	*deque_pop_back(t_deque *deque);
t_deque_node	*deque_pop_last_node(t_deque *deque);
t_deque_node	*deque_pop_front(t_deque *deque);
void			deque_pop_selected_node(t_deque *deque, \
										t_deque_node *target_node);

/* print */
void			deque_print(t_deque *deque);
void			debug_deque_print(t_deque *deque, const char *func_name);

/* set_node */
void			deque_set_next(t_deque_node *deque, t_deque_node *next);
void			deque_set_prev(t_deque_node *deque, t_deque_node *prev);

/* new */
// if malloc error, return NULL
t_deque			*deque_new(void);
t_deque_node	*deque_node_new(void *content);

#endif
