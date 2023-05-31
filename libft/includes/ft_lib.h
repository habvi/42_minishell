#ifndef FT_LIB_H
# define FT_LIB_H

# include <stddef.h>
# include <stdbool.h>

int		ft_atoi_old(const char *str);
bool	ft_atoi_strictly(const char *str, int *num);
bool	ft_atoi(const char *str, int *num);
// if malloc error, return NULL
char	*ft_itoa_int(int n);
// if malloc error, return NULL
char	*ft_itoa(int n);
bool	ft_strtol(const char *str, long *ret_num, char **endptr);

#endif
