#ifndef FT_STRING_H
# define FT_STRING_H

# include <stdbool.h>
# include <stddef.h>

/* compare */
char	*ft_strchr(char *s, int c);
bool	ft_strchr_bool(const char *s, int int_c);
char	*ft_strrchr(const char *s, int c);
bool	ft_streq(const char *s1, const char *s2);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/* iterator */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* copy */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_strlcpy_void(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/* len */
size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t maxlen);

/* return new string */
// if malloc error, return NULL
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strndup(const char *s, size_t maxlen);
//char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr_tail(char const *s, unsigned int start);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_find_set_in_str(char *str, char *set);

#endif
