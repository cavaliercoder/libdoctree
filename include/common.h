#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef UNICODE
#define DTstrdup	wcsdup
#define DTstrcmp	wcscmp
#else
#define DTstrdup	strdup
#define DTstrcmp	strcmp
#endif

void *DTalloc(void *old, size_t size);
#define DTfree		free

#endif // COMMON_H
