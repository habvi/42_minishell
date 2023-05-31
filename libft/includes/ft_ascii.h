#ifndef FT_ASCII_H
# define FT_ASCII_H

# include <stdbool.h>

bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
bool	ft_isascii(int c);
bool	ft_isdigit(int c);
bool	ft_isprint(int c);

int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
