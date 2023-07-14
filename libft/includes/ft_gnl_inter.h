#ifndef FT_GNL_INTER_H
# define FT_GNL_INTER_H

# include <stdlib.h> // malloc, free
# include <unistd.h> // read
# include <stdbool.h>
# include <limits.h>
# include "ft_string.h"

# define BUFFER_SIZE    1024
# define LF             '\n'
# define GNL_READ_ERROR (-1)

// get_next_line_utils.c
char	*ft_substr_for_gnl(char const *s, unsigned int start, size_t len);
void	*ft_memmove_for_gnl(void *dst, const void *src, size_t len);

#endif
