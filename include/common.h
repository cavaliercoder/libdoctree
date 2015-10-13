#ifndef COMMON_H
#define COMMON_H

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
#define DTstrdup	_wcsdup

#else // !UNICODE

#ifndef _T
#define _T(s)		s
#endif

#define DTfprintf	fprintf
#define DTstrlen	strlen
#define DTstrcmp	strcmp
#define DTstrdup	_strdup

#endif // UNICODE

size_t	DTmstrlen(const DTchar *str);
DTchar*	DTmstrdup(const DTchar *str);

void	*DTalloc(void *old, size_t size);
#define	DTfree		free

#endif // COMMON_H
