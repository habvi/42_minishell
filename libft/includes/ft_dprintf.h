#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <unistd.h>

// if ft_dprintf error, return ERROR_FT_DPRINTF(-1)
int	ft_dprintf(int fd, const char *format, ...);

#endif
