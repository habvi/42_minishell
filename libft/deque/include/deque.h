#ifndef DEQUE_H
# define DEQUE_H

# include <stddef.h>
# include <stdbool.h>

# include <stdio.h> // to do: erase

typedef enum e_error	t_error;

typedef struct s_deque_node {
	void				*content;
	struct s_deque_node	*next;
	struct s_deque_node	*prev;
}	t_deque_node;

typedef struct s_deque {
	t_deque_node	*node;
	size_t			size;
}	t_deque;

// dq_add_back.c
// void	deque_add_back(t_deque *deque, t_deque *new_node);

// dq_add_front.c
// void	deque_add_front(t_deque *deque, t_deque *new_node);

// dq_clear.c
void			deque_clear(t_deque **deque);

// dq_is_empty.c
bool			deque_is_empty(t_deque *deque);

// dq_new.c
t_deque			*deque_new(void);

// dq_node_new.c
t_deque_node	*deque_node_new(void *content);

// dq_pop_back.c
// t_deque	*deque_pop_back(t_deque *deque);

// dq_pop_front.c
// t_deque	*deque_pop_front(t_deque *deque);

// dq_print.c
void			deque_print(t_deque *deque);
void			debug_deque_print(t_deque *deque, const char *func_name);

// dq_set_value.c
// void	deque_set_next(t_deque *deque, t_deque *next);
// void	deque_set_prev(t_deque *deque, t_deque *prev);

#endif
