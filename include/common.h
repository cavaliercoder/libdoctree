#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef UNICODE

#ifndef _T
#define _T(s)		L ## s
#endif

#define DTfprintf	fwprintf
#define DTstrdup	wcsdup
#define DTstrcmp	wcscmp

#else // !UNICODE

#ifndef _T
#define _T(s)		s
#endif

#define DTfprintf	fprintf
#define DTstrdup	strdup
#define DTstrcmp	strcmp

#endif // UNICODE

void *DTalloc(void *old, size_t size);
#define DTfree		free

#endif // COMMON_H
