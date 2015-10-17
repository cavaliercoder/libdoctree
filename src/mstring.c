#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Return the size of a NULL separated multi-string array (including all NULL
 * separators and the final NULL terminator).
 */
size_t
mstrsize(const char *s)
{
	size_t	size;

	if (!*s)
		return 0;

	for (size = 0; *s || *(s + 1); s++)
		size++;

	return size + 2;
}

/*
 * Return the number of strings in a NULL separated multi-string array.
 */
size_t
mstrlen(const char *s)
{
	size_t size;

	if (!*s)
		return 0;

	for (size = 1; *s || *(s + 1); s++)
		if (!*s)
			size++;

	return size;
}

/*
 * Return a pointer to a string at the given index in a multi-string array.
 * Returns NULL if the index is out of bounds.
 */
char*
mstrelem(char *s, const int index)
{
	int i = 0;

	if (NULL == s || !*s)
		return NULL;

	for(i = 0; *s || *(s + 1); s++){
		if (i == index)
			return s;

		if (!*s)
			i++;
	}

	return NULL;
}

/*
 * Duplicate a NULL separated multi-string array.
 * Returns a pointer to the newly allocated multi-string.
 */
char*
mstrdup(const char *s)
{
	size_t			size = 0;
	char			*out = NULL;
	unsigned int	i = 0;

	// validate
	if (NULL == s || '\0' == *s)
		return NULL;

	size = mstrsize(s);

	// allocate
	out = malloc(sizeof(char) * (size + 1));
	if (NULL == out)
		return NULL;

	// copy
	for (i = 0; i < size; i++)
		out[i] = s[i];

	// terminate
	out[i] = '\0';

	return out;
}

/*
 *
 */
int
mstrncat(char *dest, const char *s, const size_t size)
{
	int		i = 0, destlen = 0, slen = 0, written = 0;
	char	*c = NULL;

	// validate
	if (NULL == dest || NULL == s)
		return -1;

	// get length of new string
	slen = strlen(s);

	// get length of destination multi-string
	if (!*dest)
		destlen = 0;
	else
		for (c = dest, destlen = 1; *c || *(c + 1); c++)
			destlen++;

	// copy and terminate
	for (i = 0, written = 0; i < slen && (destlen + i < size - 2); i++)
		dest[destlen + i] = s[i];

	dest[destlen + i + 1] = '\0';

	return i;
}

char*
mstrcat(char *dest, const char *s)
{
	char	*c = NULL, *out = NULL;
	size_t	destsize = 0, slen = 0;

	if (NULL == s)
		return dest;

	slen = strlen(s);

	// get move to end of destination
	for (c = dest, destsize = 0; c && (*c || *(c + 1)); c++, destsize++)
	{ }

	// init new multi-string
	out = realloc(dest, sizeof(char) * (destsize + slen + 2));
	if (NULL == out)
		return NULL;

	// append
	if (dest)
		destsize++;

	memcpy(&out[destsize], s, slen + 1);
	out[destsize + slen + 1] = '\0';

	return out;
}

/*
 * Print a multi-string to the given file stream printing the given separator
 * between each string.
 */
void
mprint(FILE *f, const char *s, const char *separator)
{
	for (; s && (*s || *(s + 1)); s++)
		if (!*s)
			fprintf(f, "%s", separator);
		else
			fputc(*s, f);
}
