#include "ft_dprintf_inter.h"
#include "ft_sys.h"

static size_t	strlen_for_printf(const char *s, t_info_pf *info)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		if (len == INT_MAX)
		{
			info->error = ERROR_OVERFLOW;
			return (0);
		}
		len++;
	}
	return (len);
}

static void	strlcpy_for_printf(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

void	strdup_for_printf(t_info_pf *info, const char *src)
{
	size_t	len_s;
	char	*dst;

	len_s = strlen_for_printf(src, info);
	if (info->error)
		return ;
	dst = (char *)x_malloc(sizeof(char) * (len_s + 1));
	if (dst == NULL)
	{
		info->error = ERROR_MALLOC;
		return ;
	}
	strlcpy_for_printf(dst, src, len_s + 1);
	info->dup_str = dst;
	if (info->type == 'c' && !len_s)
		len_s++;
	info->len_str = len_s;
}
