#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_deque	t_deque;

typedef enum e_quote {
	QUOTE_NONE = 0,
	QUOTE_SINGLE = 1,
	QUOTE_DOUBLE = 2
}	t_quote;

typedef enum e_concat {
	CONCAT_NONE = 0,
	CONCAT_PREV = 1,
	CONCAT_NEXT = 2,
	CONCAT_BOTH = 3
}	t_concat;

typedef struct s_token {
	char			*str;
	enum e_quote	quote;
	enum e_concat	concat;
}	t_token;

/* tokenize */
t_deque	*tokenize(char *line);

#endif
