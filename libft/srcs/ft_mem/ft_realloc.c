#include "ft_string.h"
#include "ft_mem.h"
#include "ft_sys.h"

// if len(src) > newsize, terminating of new_ptr is undefined
// if size == 0, and ptr != NULL, then the call is equivalent to free(src)
void	*ft_realloc(void *src, size_t newsize)
{
	void	*new_ptr;
	size_t	size;

	size = ft_strlen(src);
	if (size == newsize)
		return (src);
	new_ptr = (void *)x_malloc(sizeof(void) * newsize);
	if (src)
		ft_memcpy(new_ptr, src, newsize);
	free(src);
	return (new_ptr);
}
