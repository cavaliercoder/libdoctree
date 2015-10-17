#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
// ignore deprecated posix functions on Windows
#define _CRT_NONSTDC_NO_DEPRECATE
#endif

#include "doctree.h"
#include "mstring.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Platform character functions
 */
#ifdef _UNICODE

#define DTfputs		fputws
#define DTfprintf	fwprintf
#define DTstrlen	wcslen
#define DTstrcmp	wcscmp
#define DTstrdup	wcsdup

#else // !UNICODE

#define DTfputs		fputs
#define DTfprintf	fprintf
#define DTstrlen	strlen
#define DTstrcmp	strcmp
#define DTstrdup	strdup

#endif // UNICODE

/*
 * Functions
 */
void	*DTalloc(void *old, size_t size);
#define	DTfree		free

#endif // COMMON_H
