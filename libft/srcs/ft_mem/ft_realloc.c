#include "ft_string.h"
#include "ft_mem.h"
#include "ft_sys.h"

// new_size != 0, free(src).
void	*ft_realloc(void *src, size_t newsize)
{
	void	*new_ptr;

	new_ptr = (void *)x_malloc(sizeof(void) * newsize);
	if (!new_ptr)
		return (NULL);
	if (src)
		ft_memcpy(new_ptr, src, newsize);
	free(src);
	return (new_ptr);
}
