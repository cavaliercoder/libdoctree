#include "common.h"
#include "doctree.h"

/*
 * Allocate or reallocate memory initialized to zero.
 */
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
