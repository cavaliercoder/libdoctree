#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <strings.h>

#ifdef UNICODE
#define DTstrdup	wcsdup
#else
#define DTstrdup	strdup
#endif

#endif // COMMON_H
