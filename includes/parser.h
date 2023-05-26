#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_deque	t_deque;
typedef enum e_quote	t_quote;
typedef enum e_concat	t_concat;
typedef struct s_token	t_token;

/* parser */
t_deque	*parser(t_deque *token)

#endif //PARSER_H
