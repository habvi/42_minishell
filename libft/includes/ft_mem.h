#ifndef FT_MEM_H
# define FT_MEM_H

# include <stddef.h>

/* free */
void	*ft_free(void *ptr);
void	*free_2d_array(char ***ptr);

void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);

// if malloc error, return NULL
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *src, size_t newsize);

#endif
