#ifndef COMMON_H
#define COMMON_H

// ignore deprecated posix functions on Windows
#define _CRT_NONSTDC_NO_DEPRECATE

#include "libdoctree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _UNICODE

#ifndef _T
#define _T(s)		L ## s
#endif

#define DTfprintf	fwprintf
#define DTstrlen	wcslen
#define DTstrcmp	wcscmp
#define DTstrdup	wcsdup

#else // !UNICODE

#ifndef _T
#define _T(s)		s
#endif

#define DTfprintf	fprintf
#define DTstrlen	strlen
#define DTstrcmp	strcmp
#define DTstrdup	strdup

#endif // UNICODE

size_t	DTmstrlen(const DTchar *str);
DTchar*	DTmstrdup(const DTchar *str);

void	*DTalloc(void *old, size_t size);
#define	DTfree		free

#endif // COMMON_H
