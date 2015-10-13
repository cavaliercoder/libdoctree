#include "common.h"
#include "libdoctree.h"

void*
DTalloc(void *old, size_t size)
{
	void *new = NULL;

	if (NULL == old)
		new = calloc(1, size);
	else
		new = realloc(old, size);

	return new;
}
