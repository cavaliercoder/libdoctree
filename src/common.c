#include "common.h"
#include "libdoctree.h"

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

/*
 * Return the length of a NULL separated multi-string array (excluding the final
 * NULL terminator).
 */
size_t
DTmstrlen(const DTchar *str)
{
	size_t	size;

	for (size = 0; str; str++, size++)
		if ('\0' == *str && '\0' == *(str - 1))
			return size;

	return 0;
}

/*
 * Duplicate a NULL separated multi-string array.
 */
DTchar*
DTmstrdup(const DTchar *str)
{
	size_t	size;
	DTchar	*out;
	int		i;

	// validate
	if (NULL == str || '\0' == *str)
		return NULL;

	size = DTmstrlen(str);

	// allocate
	out = DTalloc(out, size + 1);
	if (NULL == out)
		return NULL;

	// copy
	for (i = 0; i < size; i++)
		out[i] = str[i];

	// terminate
	out[i+1] = '\0';

	return out;
}
